[X,textdata] = xlsread('afterNull.xlsx');
XZ=zscore(X);
[COEFF,SCORE,latent,tsquare] = princomp(XZ);
% [COEFF,SCORE,latent,tsquare] = princomp(XZ)
% 为了直观，定义元胞数组result1，用来存放特征值、贡献率和累积贡献率等数据
%princomp函数不返回贡献率，需要用协方差矩阵的特征值向量latent来计算
explained = 100*latent/sum(latent);%计算贡献率

[m, n] = size(X);%求X的行数和列数
result1 = cell(n+1, 4);%定义一个n+1行、4列的元胞数组
%result1中第一行存放的数据
result1(1,:) = {'特征值', '差值', '贡献率', '累积贡献率'};
%result1中第1列的第2行到最后一行存放的数据(latent)特征值
result1(2:end,1) = num2cell(latent);
%result1中第2列的第2行到倒数第2行存放的数据(latent的方差，特征值的方差)
result1(2:end-1,2) = num2cell(-diff(latent));
%result1中第3列和第4列的第2行到最后一行分别存放主成分的贡献率和累积贡献率
result1(2:end,3:4) = num2cell([explained, cumsum(explained)]);
number=2
% 为了直观，定义元胞数组result2，用来存放前2个主成分表达式的系数数据
varname = textdata(1,2:end)';%提取变量名数据
result2 = cell(n+1, number+1); %定义一个n+1行，3列的元胞数组
%result2(1,:) = {'标准化变量', '特征向量t1', '特征向量t2', '特征向量t3'};%result2的第一行数据
result2(1,:) = {'标准化变量', '特征向量t1', '特征向量t2'};%'特征向量t3'};%result2的第一行数据
result2(2:end, 1) = varname;%result2第1列
result2(2:end, 2:end) = num2cell(COEFF(:,1:number)); %存放前2个主成表达式的系数矩阵

% 为了直观，定义元胞数组result3，用来存放每一个地区总的消费性支出，以及前2个主成分的得分数据
cityname = textdata(2:end,1);%提取地区名称数据
sumXZ = sum(XZ,2);      %按行求和，提取每个地区总的消费性支出
[s1, id] = sortrows(SCORE,1);%将主成得分数据SOCRE按第一主成分得分(第一列)从小到大排序
result3 = cell(m+1, 4);%定义一个m+1行，4列的元胞数组
result3(1,:) = {'地区', '总支出', '第一主成分得分y1', '第二主成分得分y2'}; %第一行的数据
result3(2:end, 1) = cityname(id);%result3的第一列的数据，排序后的城市名
%result3第2列为按id排序的sumXZ，第3列为第一主成分得分y1，第4列为第二主成分得分y2
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

% % 为了直观，定义元胞数组result3，用来存放每一个地区总的消费性支出，以及前2个主成分的得分数据
% cityname = textdata(2:end,1);%提取地区名称数据
% sumXZ = sum(XZ,number);      %按行求和，提取每个地区总的消费性支出
% [s1, id] = sortrows(SCORE,1);%将主成得分数据SOCRE按第一主成分得分(第一列)从小到大排序
% result3 = cell(m+1, number+2);%定义一个m+1行，4列的元胞数组
% %result3(1,:) = {'','总和', '第一主成分得分y1', '第二主成分得分y2', '第二主成分得分y3'}; %第一行的数据
% result3(1,:) = {'','总和', '第一主成分得分y1', '第二主成分得分y2'}; %第一行的数据
% result3(2:end, 1) = cityname(id);%result3的第一列的数据，排序后的城市名
% %result3第2列为按id排序的sumXZ，第3列为第一主成分得分y1，第4列为第二主成分得分y2
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