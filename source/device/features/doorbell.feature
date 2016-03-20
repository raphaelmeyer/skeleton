Feature: Doorbell

  Scenario: Ring doorbell
    When I press the doorbell button
    Then the doorbell rings for about 1000 ms

  @wip
  Scenario: Prevent accidental ringing
    When I press the doorbell button for 20 ms
    Then the doorbell does not ring

