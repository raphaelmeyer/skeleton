Feature: Doorbell

  Scenario: Ring doorbell
    When I press the doorbell button
    Then the doorbell rings for about 1000 ms

  @wip
  Scenario: Notify the internet module
    When I press the doorbell button
    Then the doorbell notifies the internet module
