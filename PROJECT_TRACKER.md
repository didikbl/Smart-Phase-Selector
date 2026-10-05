# PROJECT TRACKER — SMART PHASE SELECTOR V2

**Development Duration:** 1 Week
**Project Type:** Improvement / Refactoring
**Status:** In Progress

---

## 1. Project Objective

Improve the existing **Smart Phase Selector** system by focusing on:

* Improving the Web UI
* Redesigning the software architecture
* Improving AC voltage measurement
* Adding hardware overvoltage detection
* Improving LED and buzzer signaling
* Adding a Firebase web dashboard
* Improving overall system reliability and maintainability

---

## 2. Development Strategy

The V2 development will follow this approach:

**Audit → Refactor → Improve Hardware → Improve Interface → Integrate → Validate**

Each improvement must be tested before moving to the next stage.

---

## 3. Weekly Roadmap

| Day   | Main Objective                             | Status |
| ----- | ------------------------------------------ | ------ |
| Day 1 | System Audit & Software Architecture       | ⬜      |
| Day 2 | Software Refactoring                       | ⬜      |
| Day 3 | AC Voltage Measurement Improvement         | ⬜      |
| Day 4 | Hardware Overvoltage Detection & Signaling | ⬜      |
| Day 5 | Web UI V2                                  | ⬜      |
| Day 6 | Firebase Web Dashboard                     | ⬜      |
| Day 7 | Integration & Validation                   | ⬜      |

---

# Day 1 — System Audit & Software Architecture

### Objectives

* Review the current hardware architecture
* Review the current software architecture
* Identify architectural weaknesses
* Identify duplicated or tightly coupled code
* Define clear software layers
* Define module responsibilities
* Identify interfaces between modules

### Tasks

* [ ] Review current hardware architecture
* [ ] Design new hardware architecture 
* [ ] Review protection mechanism
* [ ] Review current software architecture
* [ ] Define dependencies
* [ ] Design new software architecture 
* [ ] Define module responsibilities
* [ ] Document the new software architecture

### Target Architecture

```text
Application
     │
     ▼
Services
     │
     ▼
PAL / HAL
     │
     ▼
Drivers
     │
     ▼
Hardware
```

### Deliverable

* [ ] New software architecture defined
* [ ] New hardware architecture defined
* [ ] Architectures documented

---

# Day 2 — Software Refactoring

### Objectives

Refactor the existing software according to the new architecture.

### Tasks

* [ ] Separate application logic from hardware access
* [ ] Create or improve PAL/HAL interfaces
* [ ] Refactor phase selection logic
* [ ] Refactor safety logic
* [ ] Improve naming consistency
* [ ] Improve error handling

### Validation

* [ ] System still boots correctly
* [ ] Phase monitoring works
* [ ] Phase selection works
* [ ] Existing features remain functional
* [ ] No new compilation warnings/errors

### Deliverable

* [ ] Refactored new software architecture

---

# Day 3 — AC Voltage Measurement Improvement

### Objectives

Improve the circuit used to measure the three AC phases.

### Tasks

* [ ] Review the existing measurement circuit
* [ ] Review isolation method
* [ ] Review voltage reduction stage
* [ ] Review signal conditioning stage
* [ ] Review rectification/filtering
* [ ] Review ESP32 ADC input range
* [ ] Verify measurement accuracy
* [ ] Improve filtering
* [ ] Improve protection of the MCU input
* [ ] Define calibration procedure
* [ ] Test L1 measurement
* [ ] Test L2 measurement
* [ ] Test L3 measurement
* [ ] Compare measured voltage with reference voltage

### Validation

* [ ] L1 measurement validated
* [ ] L2 measurement validated
* [ ] L3 measurement validated
* [ ] Measurement remains within the defined accuracy target
* [ ] ADC input remains within safe limits

### Deliverable

* [ ] Improved AC voltage measurement circuit
* [ ] Updated measurement software
* [ ] Calibration procedure

---

# Day 4 — Hardware Overvoltage Detection

### Objectives

Add an independent hardware mechanism for detecting dangerous overvoltage conditions.

### Tasks

* [ ] Define overvoltage threshold
* [ ] Design hardware detection circuit
* [ ] Define isolation requirements
* [ ] Define hardware response to overvoltage
* [ ] Interface detection signal with MCU
* [ ] Implement overvoltage status handling
* [ ] Test normal voltage condition
* [ ] Test overvoltage condition
* [ ] Test recovery after overvoltage

### Safety Principle

The hardware protection must not depend exclusively on the software.

```text
AC Phase
   │
   ▼
Voltage Measurement
   │
   ├──► MCU ADC
   │
   └──► Hardware Overvoltage Detection
                │
                ▼
          Protection / Fault
```

### Deliverable

* [ ] Hardware overvoltage detection implemented
* [ ] Overvoltage detection validated

---

# Day 4 — Signaling System

### Objectives

Improve system status and fault indication.

### Tasks

* [ ] Define LED states
* [ ] Define buzzer states
* [ ] Define fault signaling patterns
* [ ] Define phase selection indication
* [ ] Define phase fault indication
* [ ] Define system startup indication
* [ ] Implement signaling module
* [ ] Test all signaling patterns

### Example

```text
System Status
│
├── Normal
├── Phase Selected
├── Phase Fault
├── Overvoltage
├── No Valid Phase
├── Switching
└── System Fault
```

### Deliverable

* [ ] LED signaling system
* [ ] Buzzer signaling system
* [ ] Signaling behavior documented

---

# Day 5 — Web UI V2

**Milestone:** `Web UI V2`

**Labels:** `web-ui` · `feature` · `monitoring`

### Objectives

Improve the local Web UI to provide clearer system monitoring, operating mode control, phase status visualization, and fault indication.

### Tasks

* [ ] Review the current Web UI
* [ ] Redesign the main page
* [ ] Improve the layout and visual hierarchy
* [ ] Add a button to switch between **Automatic Mode** and **Manual Mode**
* [ ] Display the current operating mode
* [ ] Display L1 voltage
* [ ] Display L2 voltage
* [ ] Display L3 voltage
* [ ] Display the currently selected phase
* [ ] Add status indicators for L1, L2, and L3
* [ ] Clearly indicate phases affected by **Undervoltage**
* [ ] Clearly indicate phases affected by **Overvoltage**
* [ ] Clearly indicate phases affected by **Voltage Spikes**
* [ ] Display other important phase fault conditions
* [ ] Clearly distinguish healthy and faulty phases
* [ ] Add a **green LED indicator** for normal system operation
* [ ] Add a **red LED indicator** for system faults or abnormal conditions
* [ ] Integrate the LED indicators with the existing signaling system
* [ ] Provide clear feedback when switching between Automatic and Manual modes
* [ ] Test the Web UI in both operating modes
* [ ] Test all phase status and fault indications

### Expected Result

The main Web UI should provide a clear overview of the three phases, the selected phase, the current operating mode, and any detected electrical anomalies, while allowing the user to switch between **Automatic** and **Manual** modes.
