# Drell–Yan → Dimuon Z Peak (MadGraph5 + Pythia8 + Delphes + ROOT)

Minimal demonstration of a full collider simulation and analysis chain:

\[
pp \to \mu^+ \mu^- \quad (\text{Drell–Yan})
\]

The repository shows how to generate events, simulate detector response, and reconstruct the invariant mass peak of the \( Z \) boson around \( 91\,\mathrm{GeV} \).

---

## Overview

This workflow follows the standard high-energy physics pipeline:

1. **Matrix element generation** — MadGraph5_aMC@NLO  
2. **Parton shower & hadronization** — Pythia8  
3. **Detector simulation** — Delphes  
4. **Analysis** — ROOT  

The final result is a reconstructed dimuon invariant mass spectrum showing the Breit–Wigner resonance of the \( Z \) boson.

---

## Repository structure

```
analysis/plot_zpeak.C # ROOT macro to reconstruct invariant mass
Cards/ # Run and physics configuration
mg5/drell_yan.mg5 # MG5 process definition
z_peak.png # Result plot
z_peak.pdf # Result plot (vector)
```


---

## Physics

The simulated process is the Drell–Yan mechanism:

\[
q\bar{q} \to \gamma^*/Z \to \mu^+ \mu^-
\]

Near \( \sqrt{\hat{s}} \approx m_Z \), the propagator produces a resonance described by a Breit–Wigner distribution:

\[
\frac{1}{(s - m_Z^2)^2 + m_Z^2 \Gamma_Z^2}
\]

which appears as the peak in the invariant mass distribution.

---

## Requirements

- MadGraph5_aMC@NLO (with Pythia8 and Delphes)
- ROOT ≥ 6
- A generated Delphes output file  
  `tag_1_delphes_events.root`

---

## Reproducing the analysis

Start ROOT:

```bash
root -l
```
Inside ROOT:
```cpp
TString D = gSystem->ExpandPathName("~/Pheno_Tools/MG5_aMC_v3_7_0/Delphes");
gSystem->AddIncludePath(Form("-I%s -I%s/classes -I%s/external/ExRootAnalysis", D.Data(), D.Data(), D.Data()));

.L analysis/plot_zpeak.C+

plot_zpeak("/path/to/tag_1_delphes_events.root");

```

## Output

The macro reconstructs the dimuon invariant mass:

\[
m_{\mu\mu} = \sqrt{(p_{\mu^+} + p_{\mu^-})^2}
\]

Expected result:

- Clear resonance peak near \( 91\,\mathrm{GeV} \)
- Smooth continuum from virtual photon exchange

See:

- `z_peak.png`
- `z_peak.pdf`

---

## Purpose

This repository demonstrates the ability to:

- Define a collider process
- Run a full Monte Carlo simulation chain
- Perform detector-level analysis
- Reconstruct a fundamental Standard Model resonance

---

## Author

Simulation and analysis by **Jose F. Gomez**

## Acknowledgments

This project was developed following the general workflow presented in the tutorial:

José Ruiz-Álvarez, *Monte Carlo Simulations in High-Energy Physics*, IICONHEP School (2025).  
https://indico.global/event/15402/contributions/132190/