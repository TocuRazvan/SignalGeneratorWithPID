te=0.01;
t1=37;
t2=12;
t3=3;
h1=tf([1],[t1,1]);
h2=tf([1],[t2,1]);
h3=tf([1],[t3,1]);
h1d=c2d(h1,te,'tustin')
h2d=c2d(h2,te,'tustin')
h3d=c2d(h3,te,'tustin')
h12=series(h1,h2);
h123=series(h12,h3)

[NUM,DEN]=tfdata(h123,'v')
[A,B,C,D]=tf2ss(NUM,DEN)
Q=[1 0 0 ; 0 1 0 ; 0 0 1]
R=[1]
[K,S,E]=lqr(A,B,Q,R)
A0=A-B*K
[n0,d0]=ss2tf(A0,B,C,D)
h0=tf(n0,d0)
step(h123)