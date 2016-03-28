Feature: Doorbell internet module

  @wip
  Scenario: Take a picture
    Given the internet module is connected to a doorbell
    When the doorbell rings
    Then the internet module takes a picture
    And the picture is 512 pixels wide and 512 pixels high
