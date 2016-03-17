#ifndef SKELETON_SYSTEM_TICK_H
#define SKELETON_SYSTEM_TICK_H

#ifdef __cplusplus
extern "C" {
#endif

void SystemTick_init();
void SystemTick_register(void(* notify)(void *), void * observer);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //SKELETON_SYSTEM_TICK_H
