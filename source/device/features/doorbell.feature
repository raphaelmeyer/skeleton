Feature: Doorbell

  Scenario: Ring doorbell
    When I press the doorbell button
    Then the doorbell rings for about 1000 ms
