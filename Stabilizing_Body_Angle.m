
% Problem 1: Stabilizing Body Angle

% Given physical properties
Rw = 34e-3; % Wheel radius in meters
Mw = 27e-3; % Wheel mass in kg
Mb = 263e-3; % Body mass in kg
L = 36e-3; % Center of mass to wheel axis in meters
Ib = 0.0004; % Body inertia about the wheel axis in kg*m^2
Im = 3.6e-8; % Motor armature inertia in kg*m^2
Gr = 35.57; % Gearbox ratio
g = 9.81; % Acceleration due to gravity in m/s^2
s_bar = 0.003; % Motor stall torque in Nm
omega_f = 1760; % Motor free run speed in rad/s
Vb = 7.4; % Battery voltage in volts

% Combined wheel inertia
Iw = 2 * ((Mw * Rw^2) / 2 + Gr^2 * Im);

% Transfer function from motor duty cycle to angle theta
num_G1 = Mb * g * L;
den_G1 = [Ib + Mb * L^2, 0, -Mb * g * L];
G1 = tf(num_G1, den_G1);

% Plot angle theta as MiP falls over
figure;
initial(G1);
title('MiP Angle \theta as it Falls Over');

% Design stabilizing controller D1(s)
D1 = pidtune(G1, 'PID');

% Bode plot of open-loop system
figure;
bode(G1 * D1);
title('Bode Plot of Open-loop System G1(s) * D1(s)');

% Discrete time equivalent controller D1(z)
sample_rate = 200; % 200Hz sample rate
D1z = c2d(D1, 1/sample_rate, 'tustin');

% Display the difference equation
fprintf('Difference equation for D1(z):\n');
tf(D1z)
