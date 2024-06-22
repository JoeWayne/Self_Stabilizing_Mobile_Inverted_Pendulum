
% Problem 2: Stabilizing Wheel Position

% Inner loop gain assumed to be 1 initially
inner_loop_gain = 1;

% Transfer function from wheel position to angle phi
num_G2 = [inner_loop_gain];
den_G2 = [1, 0, 0];
G2 = tf(num_G2, den_G2);

% Design stabilizing controller D2(s)
D2 = pidtune(G2, 'PID');

% Root locus of outer loop
figure;
rlocus(G2 * D2);
title('Root Locus of Outer Loop');

% Continuous time step response assuming inner loop gain of 1
figure;
step(feedback(G2 * D2, 1));
title('Continuous Time Step Response (Inner Loop Gain = 1)');

% Continuous time step response with inner loop model included
figure;
step(feedback(G2 * D2, G1 * D1));
title('Continuous Time Step Response with Inner Loop Model Included');

% Discrete time transfer function D2(z)
sample_rate_outer = 20; % 20Hz sample rate
D2z = c2d(D2, 1/sample_rate_outer, 'tustin');

% Display the difference equation
fprintf('Difference equation for D2(z):\n');
tf(D2z)
