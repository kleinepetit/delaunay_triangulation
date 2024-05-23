figure;

data = importdata('output_2.txt'); % 假设输出的文件名为 output.txt

% 从数据中提取三角形顶点坐标和连接信息
numTriangles = data(1,1);
vertices = data(2:end,:);

% 将顶点坐标和连接信息重新组织成绘制三角形的格式
faces = zeros(numTriangles, 3);
for i = 1:numTriangles 
    faces(i, :) = [i*3-2, i*3-1, i*3];
end

% 绘制三角网格
patch('Vertices', vertices, 'Faces', faces, ...
    'FaceColor', 'none', 'EdgeColor', 'k');

% 设置坐标轴标签
xlabel('X');
ylabel('Y');

% 显示图形
axis equal;
grid on;

% data = importdata('origin.points');
% 
% % 可视化数据
% figure;
% plot(data(:, 1), data(:, 2), 'b.','MarkerSize',5,'MarkerEdgeColor','black'); % 绘制数据点
% xlabel('X');
% ylabel('Y');
% axis equal;
