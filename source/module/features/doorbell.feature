Feature: Doorbell internet module

  @host
  Scenario: Take a picture of a visitor
    When the doorbell rings
    Then the internet module takes a picture

  @target
  Scenario: Take a picture of a visitor
    Given there is no picture yet
    When the doorbell rings
    Then the internet module takes a picture

  @host
  Scenario: The picture shall have certain dimensions
    When the doorbell rings
    And the internet module takes a picture
    Then the picture is 512 pixels wide and 512 pixels high

  @host @wip
  Scenario: The picture should not be upside down
    When the doorbell rings
    And the internet module takes a picture
    Then the picture is not upside down
