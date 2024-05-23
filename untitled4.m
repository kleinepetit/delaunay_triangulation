for i=1:345
    CoordinateMatrix12(i, :) = [(CoordinateMatrix11(i,1)-950)/350,(CoordinateMatrix11(i,2)-60)/550]
end

figure
scatter(CoordinateMatrix12 (:,1), CoordinateMatrix12 (:,2),'.');