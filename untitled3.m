Im = imread('rabbit.png');
CoordinateMatrix = pic2points(Im,graythresh(Im),1,1000);
scatter(CoordinateMatrix (:,1), CoordinateMatrix (:,2),'.');