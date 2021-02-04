% Proiectare solutie de control automat pri plasarea polilor in locatiile
% dorite (curs/Cap.6.4)
%PROCES
Te=0.01;
T1=3;T2=2;T3=0.3;
h1=tf([1], [T1 1]);   h2=tf([1], [T2 1]);    h3=tf([1], [T3 1]);
%h1d=c2d(h1,Te,'tustin');h2d=c2d(h2,Te,'tustin');h3d=c2d(h3,Te,'tustin');
h12=series(h1,h2) 
H_Proces=series(h12,h3)
%h1234=c2d(h123,Te,'tustin')

%Proiectare Reactie dupa stare prin plasarea polilor in locatiile dorite cu
%functia PLACE
[NUM,DEN] = tfdata(H_Proces,'v');
[A,B,C,D] = tf2ss(NUM,DEN)
%alegere poli pe baza performantelor cerute, dar se poate folosi SISOTOOL
%pentru diverse plasari de poli si generare de performante
psi=0.7;        %pt. suprareglaj de 5%
    t_rasp=5;     %timp de raspuns impus
        wn=4/(t_rasp*psi);
rlocus(H_Proces)
sgrid(psi,wn)
pause;
%Valorile polilor complex conjugati vor fi
P=[-0.49+0.0523i -0.049-0.0523i -0.0478-0.059i]
%calcul K pt a plasa polii in locatiile dorite   
K_place = place(A,B,P)
A0_place=A-B*K_place;
B0_place=B; 
C0_place=C; 
D0_place=D;  
val_proprii=eig(A0_place);
[n0_place,d0_place]= ss2tf(A0_place,B0_place,C0_place,D0_place);
H0_place=tf(n0_place, d0_place);

% Se testeaza Raspunsul sistemului in circuit inchis
%OBS: Asa trebuie sa obtinem si in Labwindows
%Reprezentarea ecuatiilor de stare in circuit inchis este: 
step(H_Proces);hold on;step(H0_place);hold off