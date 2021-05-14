graph TD
A -->|GPIO| J[fa:fa-temperature-low Thermometer]
A[fa:fa-microchip Measurement Station] -->|HTTP| B[fa:fa-microchip Indoor Station]
B -->|SMTP| C[fa:fa-envelope Email Relay]
B -->|GPIO| H[fa:fa-lightbulb LED]
B -->|GPIO| L[fa:fa-tv Display]
I[fa:fa-hand-point-down Button] -->|GPIO| B
C -->|SMTP| G[fa:fa-envelope User Email Server]
G -->|Push| D[fa:fa-phone User Device A]
G -->|Push| E[fa:fa-tablet User Device B]
G -->|Push| F[fa:fa-laptop User Device C]
H-->|Visual perception| K[fa:fa-user User]
D-->|Visual perception| K
E-->|Visual perception| K
F-->|Visual perception| K
L-->|Visual perception| K
K-->|press| I
M[fa:fa-hand-point-down Button]-->|GPIO|A
K-->|press| M
A-->|GPIO|N[fa:fa-bell Buzzer]
N-->|Visual perception| K
