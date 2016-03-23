Feature: Doorbell

  Scenario: Ring doorbell
    When I press the doorbell button
    Then the doorbell rings for about 1000 ms

  Scenario: Notify the internet module
    When I press the doorbell button
    Then the doorbell notifies the internet module

  @wip
  Scenario: Prevent accidental ringing
    When there is a short pulse on the doorbell button
    Then the doorbell does not ring
