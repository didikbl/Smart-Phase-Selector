# Auto Cut-Off Hot Plate Timer

**Auto Cut-Off Hot Plate Timer** is a simple electronic timer designed to automatically switch off a hot plate after a user-defined period and provide an audible warning when the timer expires.

The system is implemented entirely with **discrete electronic components**, without using a microcontroller. It uses an **RC timing circuit** and a **threshold detection stage** to control the automatic shut-off and audible signaling functions.

When the selected time expires, the system switches off the hot plate and activates a **buzzer for 15 seconds** to notify the user.

The project focuses on the **design, calculation, prototyping, testing, and documentation** of a simple, low-cost, and practical automatic shut-off solution for a hot plate.

---

## Project Objectives

The main objectives of this project are to:

* Design a simple timer circuit without a microcontroller.
* Allow the user to define the operating time.
* Automatically switch off the hot plate when the selected time has elapsed.
* Provide an audible warning when the timer expires.
* Activate the buzzer for 15 seconds after automatic shut-off.
* Use discrete electronic components and simple circuit principles.
* Calculate and select the appropriate components.
* Build and test a physical prototype.
* Document the design process, calculations, and test results.

---

## Main Functionalities

The system is intended to provide the following functionalities:

* User-adjustable timer.
* Timer countdown.
* Hot plate automatic shut-off.
* Switching control for the hot plate.
* Timer status indication.
* Audible warning using a buzzer.
* 15-second buzzer activation after timer expiration.
* Safe shutdown when the selected time expires.

---

## System Architecture

The system is organized around the following functional blocks:

```text
                         ┌─────────────────┐
                         │   Power Supply  │
                         └────────┬────────┘
                                  │
                                  ▼
                         ┌─────────────────┐
                         │   Timer / RC    │
                         │     Circuit     │
                         └────────┬────────┘
                                  │
                                  ▼
                         ┌─────────────────┐
                         │    Threshold    │
                         │    Detection    │
                         └────────┬────────┘
                                  │
                     Timer Expired│
                                  ▼
                       ┌──────────┴──────────┐
                       │                     │
                       ▼                     ▼
              ┌─────────────────┐   ┌─────────────────┐
              │ Switching Stage │   │  Buzzer Control │
              └────────┬────────┘   └────────┬────────┘
                       │                     │
                       ▼                     ▼
              ┌─────────────────┐   ┌─────────────────┐
              │    Hot Plate    │   │ Buzzer - 15 s   │
              └─────────────────┘   └─────────────────┘
```

The exact circuit topology and component selection will be defined during the electronic design phase.

---

## Project Requirements

The project requirements will define:

* Supply voltage and electrical constraints.
* Hot plate electrical characteristics.
* Timer operating range.
* User adjustment method.
* Required shut-off behavior.
* Buzzer activation duration.
* Audible signaling behavior.
* Component availability and cost constraints.
* Safety requirements.

---

## Design Process

The project follows a structured engineering workflow:

```text
Project Definition
        ↓
System Design
        ↓
Electronic Design
        ↓
Component Calculations & Selection
        ↓
Prototype
        ↓
Testing & Validation
        ↓
Documentation
        ↓
Finalization
```

---

## Project Structure

The repository will contain the project documentation, design files, calculations, and prototype-related resources.

```text
Auto-Cut-Off-Hot-Plate-Timer/
│
├── README.md
├── docs/
├── design/
├── calculations/
├── prototypes/
├── tests/
└── media/
```

The repository structure may evolve as the project progresses.

---

## Testing & Validation

The prototype will be tested to verify:

* Timer operation.
* Timer adjustment range.
* Timing accuracy.
* Automatic hot plate shut-off.
* Switching-stage operation.
* Buzzer activation at timer expiration.
* Buzzer activation duration of 15 seconds.
* Operation under different conditions.
* Compliance with the defined acceptance criteria.

Test results will be documented in the repository.

---

## Safety

This project involves controlling a **hot plate**, which may involve hazardous temperatures and potentially dangerous mains voltage.

Safety requirements will therefore be defined before the prototype is connected to the hot plate. The prototype must be tested progressively, with appropriate electrical protection and isolation measures.

---

## Project Status

**Status:** In development

The project is currently in the **project definition and design phase**.

---

## License

To be defined.
