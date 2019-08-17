% algoitmos de Clasificacion de datos. 
Correr1=xlsread('Correr1.xlsx');
Caminar1=xlsread('Correr2.xlsx');
Caminar2=xlsread('Caminar2.xlsx');
Caminar3=xlsread('Caminar3.xlsx');
Caminar4=xlsread('Caminar4.xlsx');
Caminar5=xlsread('Caminar5.xlsx');
Caminar6=xlsread('Caminar6.xlsx');
Correr3=xlsread('Correr3.xlsx');
Correr4=xlsread('Correr4.xlsx');

Reposo1=xlsread('Reposo1.xlsx');
Reposo2=xlsread('Reposo2.xlsx');
Reposo3=xlsread('Reposo3.xlsx');
a=2/512;
Correr3(:,2)=a*Correr3(:,2);
Correr3(:,3)=a*Correr3(:,3);
Correr3(:,4)=a*Correr3(:,4);

Reposo1(:,2)=a*Reposo1(:,2);
Reposo1(:,3)=a*Reposo1(:,3);
Reposo1(:,4)=a*Reposo1(:,4);

Caminar3(:,2)=a*Caminar3(:,2);
Caminar3(:,3)=a*Caminar3(:,3);
Caminar3(:,4)=a*Caminar3(:,4);

figure
p0=plot3(Correr3(:,2),Correr3(:,3),Correr3(:,4),'b*');
hold on
p1=plot3(Reposo1(:,2),Reposo1(:,3),Reposo1(:,4),'r*');
hold on 
%plot3(Reposo2(:,2),Reposo2(:,3),Reposo2(:,4),'g*');
%hold on 
p2=plot3(Caminar3(:,2),Caminar3(:,3),Caminar3(:,4),'m*');

title('Datos correspondientes a las 3 clases');

set(p0,'DisplayName','Actividad Alta');
set(p1,'DisplayName','Actividad Baja');
set(p2,'DisplayName','Actividad Media');

legend(gca,'show');

% para el entrenamiento se definiran las clases caminar 3 y reposo 1
x1_train=Caminar3(:,2:4);
x2_train= [Reposo1(:,2:4);Correr3(:,2:4)];
x1_test=Correr4(:,2:4);
x2_test=Correr4(:,2:4);

Ntrain_A=size(x1_train,1);
Ntrain_B=size(x2_train,1);
Ntest_A=size(x1_test,1);
Ntest_B=size(x2_test,1);

data=[x1_train;x2_train];
label=[ones(Ntrain_A,1);-ones(Ntrain_B,1)];
%options = statset('maxIter',150000);
svm=svmtrain(data',label,'kernel_function','rbf');
Ytrain=svmclassify(svm,data);
Error_train_SVM=sum(double(Ytrain~=label))/(Ntrain_A+Ntrain_B);
% Voy a ingresar datos de solo caminar a test y debería poner que es la
% clase 1
data_test=[x1_test;x2_test];
label_test=[ones(Ntest_A,1);-ones(Ntest_B,1)];

Ytest=svmclassify(svm,data_test);
Error_test_SVM=sum(double(Ytest~=label_test))/(Ntest_A+Ntest_B);
n=length(Ytest);
cont1=0;
contm1=0;
for i=1:n
if Ytest(i)==1
cont1=cont1+1;
else
    contm1=contm1+1;
end
end
if cont1>contm1
   aa='esta caminando' 
else
    bb='aun no se sabe'
    % para el entrenamiento se definiran las clases caminar 3 y reposo 1
x1_train=Reposo1(:,2:4);
x2_train=Correr3(:,2:4);
x1_test=Correr4(:,2:4);
x2_test=Correr4(:,2:4);

Ntrain_A=size(x1_train,1);
Ntrain_B=size(x2_train,1);
Ntest_A=size(x1_test,1);
Ntest_B=size(x2_test,1);

data=[x1_train;x2_train];
label=[ones(Ntrain_A,1);-ones(Ntrain_B,1)];
%options = statset('maxIter',150000);
svm=svmtrain(data',label,'kernel_function','rbf');
Ytrain=svmclassify(svm,data);
Error_train_SVM=sum(double(Ytrain~=label))/(Ntrain_A+Ntrain_B);
% Voy a ingresar datos de solo caminar a test y debería poner que es la
% clase 1
data_test=[x1_test;x2_test];
label_test=[ones(Ntest_A,1);-ones(Ntest_B,1)];

Ytest1=svmclassify(svm,data_test);
Error_test_SVM=sum(double(Ytest1~=label_test))/(Ntest_A+Ntest_B);
cont1=0;
contm1=0;
for i=1:n
if Ytest1(i)==1
cont1=cont1+1;
else
    contm1=contm1+1;
end
end
if cont1>contm1
    aa='esta en reposo'
else
    es='esta corriendo'
end
end


% data=[x1_train;x2_train];
% label=[ones(Ntrain_A,1);-ones(Ntrain_B,1)];
% data_test=[x1_test;x2_test];
% label_test=[ones(Ntest_A,1);-ones(Ntest_B,1)];
% net=feedforwardnet([16 8]);
% net.trainFcn='trainlm';
% net.performFcn='mse';
% net.layers{3}.transferFcn='tansig';
% net.trainParam.epochs=100;
% net=train(net,data',label');
% view(net);
% Ytrain=net(data');
% Error_train_FNN_16_8=sum(double(sign(Ytrain)'~=label))/(Ntrain_A+Ntrain_B)
% Ytest=net(data_test');
% Error_test_FNN_16_8=sum(double(sign(Ytest)'~=label_test))/(Ntest_A+Ntest_B)
% 
