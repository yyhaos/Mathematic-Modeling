[X,textdata] = xlsread('afterNull.xlsx');
XZ=zscore(X);
[COEFF,SCORE,latent,tsquare] = princomp(XZ);
% [COEFF,SCORE,latent,tsquare] = princomp(XZ)
% Ϊ��ֱ�ۣ�����Ԫ������result1�������������ֵ�������ʺ��ۻ������ʵ�����
%princomp���������ع����ʣ���Ҫ��Э������������ֵ����latent������
explained = 100*latent/sum(latent);%���㹱����

[m, n] = size(X);%��X������������
result1 = cell(n+1, 4);%����һ��n+1�С�4�е�Ԫ������
%result1�е�һ�д�ŵ�����
result1(1,:) = {'����ֵ', '��ֵ', '������', '�ۻ�������'};
%result1�е�1�еĵ�2�е����һ�д�ŵ�����(latent)����ֵ
result1(2:end,1) = num2cell(latent);
%result1�е�2�еĵ�2�е�������2�д�ŵ�����(latent�ķ������ֵ�ķ���)
result1(2:end-1,2) = num2cell(-diff(latent));
%result1�е�3�к͵�4�еĵ�2�е����һ�зֱ������ɷֵĹ����ʺ��ۻ�������
result1(2:end,3:4) = num2cell([explained, cumsum(explained)]);
number=2
% Ϊ��ֱ�ۣ�����Ԫ������result2���������ǰ2�����ɷֱ��ʽ��ϵ������
varname = textdata(1,2:end)';%��ȡ����������
result2 = cell(n+1, number+1); %����һ��n+1�У�3�е�Ԫ������
%result2(1,:) = {'��׼������', '��������t1', '��������t2', '��������t3'};%result2�ĵ�һ������
result2(1,:) = {'��׼������', '��������t1', '��������t2'};%'��������t3'};%result2�ĵ�һ������
result2(2:end, 1) = varname;%result2��1��
result2(2:end, 2:end) = num2cell(COEFF(:,1:number)); %���ǰ2�����ɱ��ʽ��ϵ������

% Ϊ��ֱ�ۣ�����Ԫ������result3���������ÿһ�������ܵ�������֧�����Լ�ǰ2�����ɷֵĵ÷�����
cityname = textdata(2:end,1);%��ȡ������������
sumXZ = sum(XZ,2);      %������ͣ���ȡÿ�������ܵ�������֧��
[s1, id] = sortrows(SCORE,1);%�����ɵ÷�����SOCRE����һ���ɷֵ÷�(��һ��)��С��������
result3 = cell(m+1, 4);%����һ��m+1�У�4�е�Ԫ������
result3(1,:) = {'����', '��֧��', '��һ���ɷֵ÷�y1', '�ڶ����ɷֵ÷�y2'}; %��һ�е�����
result3(2:end, 1) = cityname(id);%result3�ĵ�һ�е����ݣ������ĳ�����
%result3��2��Ϊ��id�����sumXZ����3��Ϊ��һ���ɷֵ÷�y1����4��Ϊ�ڶ����ɷֵ÷�y2
result3(2:end, 2:end) = num2cell([sumXZ(id), s1(:,1:2)]);
result3;

k1=cell2mat(result1(2,3))
k2=cell2mat(result1(3,3))
% k1=result1(2,3)
% k2=result1(3,3)

for i = (2:m)
    result3{i,2}=((cell2mat(result3(i, 3))*k1)+(cell2mat(result3(i, 4))*k2));
end
result3=result3(2:end,1:2);
b=sortrows(result3,2)

% % Ϊ��ֱ�ۣ�����Ԫ������result3���������ÿһ�������ܵ�������֧�����Լ�ǰ2�����ɷֵĵ÷�����
% cityname = textdata(2:end,1);%��ȡ������������
% sumXZ = sum(XZ,number);      %������ͣ���ȡÿ�������ܵ�������֧��
% [s1, id] = sortrows(SCORE,1);%�����ɵ÷�����SOCRE����һ���ɷֵ÷�(��һ��)��С��������
% result3 = cell(m+1, number+2);%����һ��m+1�У�4�е�Ԫ������
% %result3(1,:) = {'','�ܺ�', '��һ���ɷֵ÷�y1', '�ڶ����ɷֵ÷�y2', '�ڶ����ɷֵ÷�y3'}; %��һ�е�����
% result3(1,:) = {'','�ܺ�', '��һ���ɷֵ÷�y1', '�ڶ����ɷֵ÷�y2'}; %��һ�е�����
% result3(2:end, 1) = cityname(id);%result3�ĵ�һ�е����ݣ������ĳ�����
% %result3��2��Ϊ��id�����sumXZ����3��Ϊ��һ���ɷֵ÷�y1����4��Ϊ�ڶ����ɷֵ÷�y2
% result3(2:end, 2:end) = num2cell([sumXZ(id), s1(:,1:number)]) 
% minn=999;
% for i = (2:m)
%     if minn>cell2mat(result3(i,2)) 
%         if cell2mat(result3(i,2))<-60.6
%             continue
%         end
%             minn=cell2mat(result3(i,2));
%         name=result3(i,1);
%     end
% end
% name
% minn