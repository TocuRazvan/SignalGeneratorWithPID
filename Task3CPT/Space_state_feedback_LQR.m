% Proiectare solutie de control automat pri metoda LQR (curs/Cap.7)
%PROCES
Te=0.01;
T1=3;
T2=2;
T3=0.3;
h1=tf([1], [T1 1])
h2=tf([1], [T2 1])  
h3=tf([1], [T3 1])
%h1d=c2d(h1,Te,'tustin');h2d=c2d(h2,Te,'tustin');h3d=c2d(h3,Te,'tustin');
h12=series(h1,h2)
H_Proces=series(h12,h3)
%h1234=c2d(h123,Te,'tustin')

%Proiectare Reactie dupa stare prin Metoda LQR
[NUM,DEN] = tfdata(H_Proces,'v')
[A,B,C,D] = tf2ss(NUM,DEN)
Q=[ 100  0  0;
    0  0.8  0;
    0  0  0.000001];
R=[3500];
%FUNCTIA LQR
[K,S,E] = lqr(A,B,Q,R)
% Se testeaza Raspunsul sistemului in circuit inchis
%OBS: Asa trebuie sa obtinem si in Labwindows
%Reprezentarea ecuatiilor de stare in circuit inchis este: 
A0=A-B*K
B0=B
C0=C
D0=D
[n0,d0]= ss2tf(A0,B0,C0,D0);
H0=tf(n0, d0);
step(H_Proces);
hold on
step(H0);
hold off




