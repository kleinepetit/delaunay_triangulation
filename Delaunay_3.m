figure

data = importdata('output_3.txt'); % 假设输出的文件名为 output.txt

% 从数据中提取三角形顶点坐标和连接信息
numTriangles = data(1,1);
vertices = data(2:end,:);

% 将顶点坐标和连接信息重新组织成绘制三角形的格式
faces = zeros(numTriangles, 4);
for i = 1:numTriangles 
    faces(i, :) = [i*4-3, i*4-2, i*4-1, i*4];
end

colors = zeros(numTriangles, 3);
for i = 1:numTriangles
    colors(i, :)= rand(1,3);
end
alphas = 0.5;

% 绘制三角网格
patch('Vertices', vertices, 'Faces', faces, 'FaceVertexCData' ...
    , colors, 'FaceColor', 'flat', 'EdgeColor', 'k','FaceAlpha', alphas);

% 显示图形
axis equal;
grid on;