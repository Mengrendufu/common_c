# common_c

Some common modules in C for embedded development.

## TimeEvt（草案）

静态链表驱动的通用时间事件。公共模块负责倒计时、周期重装和到期交付，
不依赖 SST、FreeRTOS、设备时钟或具体事件格式。原有 `Timer` 保持独立。

- 接口：`include/time_evt.h`
- 实现：`src/time_evt/time_evt.c`
- 宿主测试及示例 port：`test/time_evt/`

### 注册、计时与交付

```c
static unsigned const event = 42U;
static TimeEvt timer;

static void deliver(void *context, void const *event) {
    /* 使用 context 向接收方入列；由适配端解释事件类型。 */
}

static TimeEvt_PostOperations const delivery = {
    .context = NULL,
    .post = deliver
};

/* 在并发运行之前，只构造、注册一次。 */
TimeEvt_ctor(&timer, &event, &delivery);

/* 第 150 拍单次到期；若驱动频率为 100 Hz，名义延时为 1.5 s。 */
TimeEvt_arm(&timer, 150U, 0U);

/* 由外部单一驱动者周期调用，不允许重入。 */
TimeEvt_tick();

/* 停止后续到期；返回此前是否仍在计时。 */
(void)TimeEvt_disarm(&timer);
```

`delay` 必须大于零。`interval=0` 为单次，正数为周期；例如 `(1,1)`
每拍到期，`(2,4)` 在第二拍首次到期，此后每四拍到期。重新 arm 替换
当前倒计时，首次递减发生在下一拍，因此存在一拍的相位不确定性。

节点借用不透明的 `void const *event`，不解析、不修改、不分配或回收。
节点、非空事件、operations 及 context 必须覆盖计时与排队交付的完整
生命周期。构造完成后不允许复制节点、修改其成员、重新绑定或注销。
静态事件的信号、引用计数及 GC 规则均由使用者负责。

交付回调在临界区外执行，需要及时返回，不能递归驱动 tick 或修改
注册链表；可以在遵守 port 同步约定的前提下调用 arm/disarm。
同一拍内跨节点的回调执行顺序不作为业务契约。

### Port 契约

使用方提供 `time_evt_port.h`，并将该头所在目录加入包含路径：

| 宏 | 职责 |
|---|---|
| `TIME_EVT_REQUIRE(condition)` | 契约失败时停止执行，不能忽略后继续 |
| `TIME_EVT_CRIT_STAT` | 声明临界区所需的局部状态，允许展开为空 |
| `TIME_EVT_CRIT_ENTRY()` | 序列化共享计数的读写 |
| `TIME_EVT_CRIT_EXIT()` | 恢复进入前的同步状态 |

port 必须保证计数更新之间的互斥与内存可见性；ISR 是否能调用
arm/disarm 也由 port 决定。仅在完全串行使用时，临界区才可为空实现。
模块不默认关闭断言或使用空锁。测试 port 展示了状态保存/恢复的形状，
用于宿主顺序及交错测试，不是可直接用于多线程互斥的实现。

到期在临界区内提交，之后才调用 post。因此 disarm 不能撤回已提交
的到期，即使回调尚未执行；也不撤回已入列的消息。重新 arm 同样不
撤回旧消息。需要取消后重新进入等业务协议时，由使用者处理旧消息。

### 宿主验证

在仓库根目录运行，产物写到 `/tmp`：

```sh
gcc -std=c11 -Wall -Wextra -Werror \
  -fsanitize=address,undefined -fno-pie -no-pie \
  -Iinclude -Itest/time_evt \
  src/time_evt/time_evt.c test/time_evt/test_time_evt.c \
  -o /tmp/common-time-evt-test
/tmp/common-time-evt-test
```

覆盖不同事件类型和接收方、单次/周期、重 arm、disarm、到期与取消
交错，以及重复注册等契约。该草案尚未接入下游工程。
