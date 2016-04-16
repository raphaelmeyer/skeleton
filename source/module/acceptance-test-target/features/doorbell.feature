Feature: Doorbell internet module

  Scenario: Take a picture of a visitor
    Given there is no picture yet
    When the doorbell rings
    Then the internet module takes a picture
