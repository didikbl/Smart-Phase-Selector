# ⚡ Smart Phase Selector

> An MCU-based intelligent phase selection system designed to maintain power continuity by selecting the best and safest phase from a three-phase electrical network.

## 📖 Overview

**Smart Phase Selector** is an embedded system designed to automatically manage the power supply of a single-phase load connected to a three-phase electrical network.

The system continuously monitors **L1, L2 and L3**, measures their electrical conditions, and automatically selects the **best suitable phase** to supply the load.

The selection is therefore not based solely on phase availability.

A phase with an abnormal voltage, particularly an **overvoltage condition**, is automatically excluded from the selection process.

The project combines:

* Three-phase electrical monitoring
* Automatic phase selection
* Overvoltage protection
* MCU-based control
* LCD monitoring
* Local Web UI
* IoT Web dashboard

---

## 🎯 Objectives

The main objectives are to:

* Maintain power continuity for the connected load.
* Continuously monitor the three phases.
* Measure the voltage of each phase.
* Identify phases with acceptable voltage conditions.
* Automatically exclude phases with dangerous overvoltage.
* Select the best suitable phase among the admissible phases.
* Protect the load against abnormal voltage conditions.
* Prevent simultaneous connection of multiple phases.
* Provide local and remote system monitoring.

---

## ⚡ Intelligent Phase Selection

Unlike a conventional phase selector that simply checks whether a phase is present or absent, **Smart Phase Selector evaluates the voltage of each phase before making a selection**.

The general principle is:

```text
              L1 ──► Voltage measurement ──┐
                                           │
              L2 ──► Voltage measurement ──┼──► Evaluation
                                           │
              L3 ──► Voltage measurement ──┘
                                                  │
                                                  ▼
                                      ┌────────────────────┐
                                      │ Safety evaluation  │
                                      └─────────┬──────────┘
                                                │
                               ┌────────────────┴────────────────┐
                               │                                 │
                         Safe voltage                    Overvoltage
                               │                                 │
                               ▼                                 ▼
                         Candidate phase                   EXCLUDED
                               │
                               ▼
                     Best phase selected
```

---

## 🛡️ Overvoltage Protection

One of the key features of Smart Phase Selector is **overvoltage protection through phase exclusion**.

If a phase exceeds the permitted voltage range:

```text
Lx voltage > maximum permitted voltage
                    ↓
              Phase rejected
                    ↓
        Phase cannot be selected
```

The affected phase remains isolated from the load selection until its voltage returns to an acceptable range.

This prevents the system from connecting the load to a phase that could potentially damage the connected equipment.

---

## 📊 Phase Evaluation

Each phase can be classified according to its electrical condition.

For example:

```text
Phase voltage
     │
     ├── Too low      → Reject / according to system policy
     │
     ├── Acceptable   → Candidate
     │
     └── Too high     → Reject immediately
```

Among the phases considered safe, the controller determines which one provides the **best operating condition** for the load.

The selection strategy can therefore take into account:

* Voltage level
* Acceptable operating range
* Phase availability
* Safety status
* Selection priority
* Current active phase

---

## 🔄 Automatic Phase Selection

The MCU continuously evaluates the three phases.

For example:

```text
L1 = 230 V  → Acceptable
L2 = 242 V  → Acceptable
L3 = 275 V  → Overvoltage → REJECTED
```

The system therefore considers only:

```text
L1 = 230 V
L2 = 242 V
```

and selects the phase according to the defined selection strategy.

If the currently selected phase becomes unsafe, the system can automatically switch to another admissible phase.

---

## 🔌 Power Switching

The MCU controls the power switching stage responsible for connecting the selected phase to the load.

The fundamental rule is:

> **Only one phase can be connected to the load at a time.**

The switching system must provide appropriate electrical and logical interlocking to prevent simultaneous phase connection.

---

## 🧠 MCU-Based Control

The MCU is responsible for the system's main control functions:

* Phase voltage monitoring
* Phase condition evaluation
* Overvoltage detection
* Phase exclusion
* Best-phase selection
* Contactor control
* System state management
* Fault management
* LCD management
* Web UI management
* IoT communication

This makes the selector programmable, configurable and expandable.

---

## 🖥️ LCD Interface

The local LCD provides real-time information about the system.

It can display:

* L1 voltage
* L2 voltage
* L3 voltage
* Selected phase
* Phase status
* Overvoltage warnings
* System status
* Communication status

Example:

```text
L1: 230V  OK
L2: 242V  OK
L3: 275V  HIGH

ACTIVE: L1
```

---

## 🌐 Local Web UI

The system provides a local Web interface accessible from a smartphone or computer.

The Web UI can provide:

* Real-time phase voltages
* Phase status
* Active phase
* Rejected phases
* Overvoltage conditions
* System status
* Configuration
* Authorized manual controls

---

## ☁️ IoT Web Dashboard

Smart Phase Selector can also provide remote monitoring through an IoT Web dashboard.

The dashboard can provide:

* Real-time phase voltages
* Active phase
* Phase availability
* Rejected phases
* Overvoltage events
* System status
* Events and alerts
* Historical measurements

The core protection and phase-selection functions remain local to the device and do not depend on Internet availability.

---

## 🧩 System Overview

```text
                  THREE-PHASE NETWORK
                    L1    L2    L3
                     │     │     │
                     ▼     ▼     ▼
              ┌──────────────────────┐
              │   VOLTAGE MONITORING │
              └──────────┬───────────┘
                         │
                         ▼
              ┌──────────────────────┐
              │         MCU          │
              │                      │
              │ Voltage Evaluation   │
              │ Safety Evaluation    │
              │ Phase Selection      │
              │ State Management     │
              └───────┬───────┬──────┘
                      │       │
              ┌───────┘       └───────────────┐
              ▼                               ▼
       ┌─────────────┐                 ┌──────────────┐
       │   POWER     │                 │  INTERFACES  │
       │  SWITCHING  │                 │              │
       └──────┬──────┘                 │ LCD          │
              │                        │ Web UI       │
              ▼                        │ IoT          │
        SINGLE-PHASE                   └──────────────┘
            LOAD
```

---

## 🚀 Development Roadmap

### Phase 1 — Voltage Monitoring

* Three-phase voltage measurement
* Voltage evaluation
* Phase status detection
* Overvoltage detection

### Phase 2 — Intelligent Selection

* Phase selection logic
* Safe-phase filtering
* Best-phase selection
* Contactor control
* Interlocking

### Phase 3 — Local Interface

* LCD integration
* Real-time measurements
* Active phase display
* Fault and overvoltage indication

### Phase 4 — Web UI

* Local Web server
* Real-time monitoring
* Configuration
* Authorized manual controls

### Phase 5 — IoT

* IoT connectivity
* Remote Web dashboard
* Events and alerts
* Historical measurements

### Phase 6 — Reliability & Protection

* Voltage abnormality testing
* Overvoltage testing
* Phase failure testing
* Phase recovery testing
* Switching validation
* Long-duration testing

---

## 🛡️ Safety

Smart Phase Selector is designed around a fundamental principle:

> **An electrically unsafe phase must never be selected.**

The system must provide appropriate protection and isolation between the three-phase power network and the low-voltage control electronics.

It must also prevent:

* Simultaneous phase connection
* Phase-to-phase short circuits
* Selection of an overvoltage phase
* Unsafe switching conditions
* Unintended energization of the load

> ⚠️ This project involves potentially hazardous electrical voltages. Prototype construction and testing must be performed using appropriate electrical protection and safety procedures.

---

## 📊 Project Status

**Status:** 🚧 Development

The project follows an iterative engineering approach:

```text
Measure
   ↓
Evaluate
   ↓
Protect
   ↓
Select
   ↓
Switch
   ↓
Monitor
   ↓
Improve
```

---

## 🎓 Learning Objectives

Smart Phase Selector combines several engineering domains:

* Three-phase electrical systems
* Voltage measurement
* Overvoltage protection
* Automatic phase selection
* Power switching
* Contactor control
* Electrical interlocking
* MCU programming
* LCD interfaces
* Web applications
* IoT
* Remote monitoring
* Fault management

The project demonstrates how a conventional electrical automation problem can be transformed into an **intelligent, connected and protection-oriented embedded system**.

---

## 📌 Project

**SMART PHASE SELECTOR**

**Core principle:**

> **Measure → Evaluate → Protect → Select → Switch → Monitor**

**Control:** MCU-based
**Input:** Three-phase electrical network
**Output:** Single-phase load
**Protection:** Overvoltage phase exclusion
**Interfaces:** LCD + Local Web UI + IoT Web Dashboard
