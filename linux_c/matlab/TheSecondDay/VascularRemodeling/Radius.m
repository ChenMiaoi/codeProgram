% 问题分析{
%       如何求取半径：
%           对第i 张切片上的第j个内点，求到边界点k的距离Sjk,
%           从中选取一个最小距离Sj=min{Sjk}再从中选取一个最大的,记为ri=max{Sj}.
%           不难理解，这就是第i张切片的最大内切圆的半径。相应的内点即为圆心（中轴线与截面的交点）。
%           对100张切片搜索后就得到100个球心点。
% }
%
% params{
%       path_file           文件路径
%       Img                 获取的每一张图片的二值图(灰度图
%       img                 反转后的二值图(灰度图
%       contour             获取的每一张图片的轮廓，采用边缘检测算法
%       skeleton            获取的每一张图片的骨架，采用形态学运算提取出骨架
%       size_contr          轮廓灰色区域的个数
%       size_skel           骨架灰色区域的个数
%       inscribed_radius    建立零矩阵求内切圆半径，用来存储每一张图片的内切圆半径
%       center_focus        建立二维零矩阵存放中心点坐标， 用来存储每一张图片的内切圆圆心
%                           第一维度是存放最小圆心
%                           第二维度是存放最小半径坐标集
%       min_radi            最小半径            
%       min_focus           最小圆心
%       min_radi            最大半径
%       max_focus           最大圆心
% }
%
% return{
%       result              存放获取的结果
%                           第一维度存放的是X轴的点集
%                           第二维度存放的是Y轴的点集
%                           第三维度存放的是Z轴的点集
%                           第四维度存放的是最大半径
% }

function [result] = Radius(path_file)
    result = zeros(100, 4); % 存储最后的结果，分别为x轴坐标，y轴坐标，z轴坐标以及半径
    for k = 0 : 99
        img_name = strcat(int2str(k), ".bmp");
        img_name = fullfile(path_file, img_name); % 每一张图片的文件路径
        Img = imread(img_name); % 读取每一张图片的像数值，是二值图

        for i = 1 : 512 % 图片的像素为512 * 512
            for j = 1 : 512
                img(i, j) = ~Img(i, j); % 将二值图反转，黑变白，白变黑，黑色为1， 白色为0
                % 为了后面find函数查找1并且记录
            end
        end
        % fprintf("img (%d), Img(%d)\n", img(1, 1), Img(1, 1));
        % gray_img = imbinarize(img, "global");
        contour = edge(img, 'canny'); % 边缘检测，使用canny算子，提取灰度图的轮廓
        skeleton = bwmorph(img, "skeleton", inf); % 提取灰度图的骨架
        % bwmorph是一种二维图像的形态学运算， skeleton是提取出骨架，获取到图像的骨架特征
        % imshow(skeleton); % 骨架
        % imshow(contour); % 轮廓
        [x0, y0, v0] = find(contour); % 查找非零元素的索引和值,也就是1，而1就是轮廓的灰色区域
        [x1, y1, v1] = find(skeleton); % 找到骨架灰色的区域
        
        size_contr = length(x0); % 轮廓灰色区域的个数
        size_skel = length(x1); % 骨架灰色区域的个数
    
        inscribed_radius = zeros(size_contr, size_skel); % 建立零矩阵求内切圆半径
        center_focus = zeros(size_contr, 2); % 建立二维零矩阵存放中心点坐标
        for i = 1 : size_skel % 对骨架各点进行遍历
            p1 = x1(i);
            q1 = y1(i);
            for j = 1 : size_contr % 对轮廓各点进行遍历
                p2 = x0(j);
                q2 = y0(j);
                inscribed_radius(i, j) = sqrt((p1 - p2)^2 + (q1 - q2)^2); % 通过循环求各个骨架上的各个点到轮廓的距离
            end
            [min_radi, min_focus] = min(inscribed_radius(i, : ));
            % 骨架上一点到轮廓的最短距离，即骨架上各个点为圆心的内切园的半径
            % min_radi最小半径， min_focus最小半径坐标
            center_focus(i, 1) = min_radi; % 存放最小半径
            center_focus(i, 2) = min_focus; % 存放最小半径坐标
        end
        [max_radi, max_focus] = max(center_focus(:, 1));
        % 找到其中最大的半径，并把半径和圆心坐标存储
    
        % 存放结果
        x = x1(max_focus) - 256; % 与题目所给坐标轴对应 
        y = y1(max_focus) - 256; % 与题目所给坐标轴对应 
        result(k + 1, 1) = x; % X轴坐标 
        result(k + 1, 2) = y; % Y轴坐标 
        result(k + 1, 3) = k + 1; % Z轴坐标 
        result(k + 1, 4) = max_radi; % 半径 
    end
    % xlswrite("Radius.xls", result);
end

