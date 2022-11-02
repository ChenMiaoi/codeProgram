function [new_status] = operation(status, move)
    dir = status(end);
    % dir = -dir;
    move = [move, 0];
    new_status = status(1, :) + dir * move;
end

