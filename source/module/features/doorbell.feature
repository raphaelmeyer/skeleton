Feature: Doorbell internet module

  Scenario: Take a picture of a visitor
    When the doorbell rings
    Then the internet module takes a picture

  Scenario: The picture shall have certain dimensions
    When the doorbell rings
    And the internet module takes a picture
    Then the picture is 512 pixels wide and 512 pixels high

  @wip
  Scenario: The picture should not be upside down
    When the doorbell rings
    And the internet module takes a picture
    Then the picture is not upside down
