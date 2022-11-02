function [flag] = checkStatusSet(status)
    % checkStatusSet 检查该状态是否在允许状态集中
    % return{
    %       flag = 1 -> yes
    %       flag = 0 -> no
    % }
    permit_status = [
        3 3 1;
        3 2 1;
        3 1 1;
        3 0 1;
        2 2 1;
        0 0 1;
        0 3 1;
        0 2 1;
        0 1 1;
        1 1 1
    ]; % 一共十种状态被允许，其规则为S={(x,y)|x=0或3,y=0,1,2,3;x=y=1,2}
    temp = permit_status; % 因为过河有两种状态，一种是过，一种是回，因此需要再加入过河的状态
    temp(:, end) = -temp(:, end); % 更替允许因子
    permit_status = [permit_status; temp]; % 此时有十种状态被允许，但分为了两种状态
    flag = 0;
    for i = 1 : size(permit_status, 1)
        if sum(status == permit_status(i, : )) == 3
            flag = 1;
        end
    end
end

