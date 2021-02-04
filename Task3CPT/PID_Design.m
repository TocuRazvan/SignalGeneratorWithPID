clc;
clear;
num=[0 1]%
den=[1332 591 52 1]% poles: P1=-17.9443, P2=-0.0557
G=tf(num,den)% poles are negative that's your system is srtbale
[C_PID, info]=pidtune(G,'PIDF');
info
% the previous instrution gives the PID paprametrs and the chosen open-loop crossover
% frequency
%you can test your PID using the step response as follows:
T_PID=feedback(C_PID*G,1)
hold on
step(T_PID)
% the previous PID has crossover frequency of 0.0985 rad/s
% if you want a faster response, you have to change the open-loop crossover
% frequency, for example
[C_PID_fast, info]=pidtune(G,'PIDF',1.0)
TI_PD_fast=feedback(C_PID_fast*G,1)
hold on
step(TI_PD_fast)

