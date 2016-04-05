# device

- Execute device loop only once per tick, idle/sleep mode
- device initialization, how to share between exe and feature?
- share device seams between tests and features
- refactor gpio tests, fixtures, but still test port and pin association
- gpio tests get direction
- button: push, press ...

# module

- split interrupt into thin sys call layer, and doorbell functionality
- feature test boundary for interrupt
- feature test boundary for shell command
- drive interrupt implementation not to be blocked if a handler blocks -> event class?
- catch sigterm for shutdown
