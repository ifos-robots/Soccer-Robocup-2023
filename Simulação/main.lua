function moveforward()
    -- move forward code
    sim.setJointTargetVelocity(motor1_handle, -0.866 * 3)
    sim.setJointTargetVelocity(motor2_handle, 0)
    sim.setJointTargetVelocity(motor3_handle, 0.866 * 3)
end

function movebackward()
    -- movebackward code
    sim.setJointTargetVelocity(motor1_handle, 0.866 * 3)
    sim.setJointTargetVelocity(motor2_handle, 0)
    sim.setJointTargetVelocity(motor3_handle, -0.866 * 3)
end

function diagonalRT()
    -- movebackward code
    sim.setJointTargetVelocity(motor1_handle, -1.366 * 3)
    sim.setJointTargetVelocity(motor2_handle, 1 * 3)
    sim.setJointTargetVelocity(motor3_handle, 0.366 * 3)
end

function diagonalLF()
    -- movebackward code
    sim.setJointTargetVelocity(motor1_handle, -0.366 * 3)
    sim.setJointTargetVelocity(motor2_handle, -1 * 3)
    sim.setJointTargetVelocity(motor3_handle, 1.366 * 3)
end

function turnleft()
    -- turnleft code
    sim.setJointTargetVelocity(motor1_handle, 0.5 * 3)
    sim.setJointTargetVelocity(motor2_handle, -1 * 3)
    sim.setJointTargetVelocity(motor3_handle, 0.5 * 3)
end

function turnright()
    -- turnright code
    sim.setJointTargetVelocity(motor1_handle, -0.5 * 3)
    sim.setJointTargetVelocity(motor2_handle, 1 * 3)
    sim.setJointTargetVelocity(motor3_handle, -0.5 * 3)
end

function rotleft()
    -- rotleft code
    sim.setJointTargetVelocity(motor1_handle, 1 * 3)
    sim.setJointTargetVelocity(motor2_handle, 1 * 3)
    sim.setJointTargetVelocity(motor3_handle, 1 * 3)
end

function rotright()
    -- rotleft code
    sim.setJointTargetVelocity(motor1_handle, -1 * 3)
    sim.setJointTargetVelocity(motor2_handle, -1 * 3)
    sim.setJointTargetVelocity(motor3_handle, -1 * 3)
end

function stop()
    -- stop code
    sim.setJointTargetVelocity(motor1_handle, 0)
    sim.setJointTargetVelocity(motor2_handle, 0)
    sim.setJointTargetVelocity(motor3_handle, 0)
end

function inverseKinematics(vx, vy, w)
    v1 = -(vx + math.sqrt(3) * vy) / 2 + L * w
    v2 = vx + w * L
    v3 = (-vx + math.sqrt(3) * vy) / 2 + L * w
    return v1, v2, v3
end

function getDistance(target)
    result, distanceData, objectHandlePair = sim.checkDistance(midpoint, target)
    return distanceData[7]
end

function rotate(val)
    if (val > 0) then
        sim.setJointTargetVelocity(motor1_handle, 1)
        sim.setJointTargetVelocity(motor2_handle, 1)
        sim.setJointTargetVelocity(motor3_handle, 1)
    elseif (val < 0) then
        sim.setJointTargetVelocity(motor1_handle, -1)
        sim.setJointTargetVelocity(motor2_handle, -1)
        sim.setJointTargetVelocity(motor3_handle, -1)
    end
end

function correctAngle(theta)
    v1, v2, v3 = inverseKinematics(0, 0, theta)
    print('angle')

    --    print(compassData[3])
    speed = math.max(math.min(theta, 1), 2)
    --print(speed)

    v1 = v1 / theta * speed
    if (theta < 0) then
        v1 = v1 * -1
    end
    v2 = v1
    v3 = v1
    --print(v1)
    move(v1, v2, v3)
end

function getDistanceSensor(sensor, max_dist)
    local detected, distance
    detected, distance = sim.readProximitySensor(sensor)
    if (detected < 1) then
        distance = max_dist
    end
    return distance
end

function isSpining()
    if (sim.getJointTargetVelocity(motor1_handle) == sim.getJointTargetVelocity(motor2_handle) and sim.getJointTargetVelocity(motor1_handle) == sim.getJointTargetVelocity(motor3_handle)) then
        if (sim.getJointTargetVelocity(motor1_handle) == 0) then
            return false
        else
            return true
        end
    else
        return false
    end
end

function isMoving()
    if (sim.getJointTargetVelocity(motor1_handle) ~= 0 or sim.getJointTargetVelocity(motor2_handle) ~= 0 or sim.getJointTargetVelocity(motor3_handle) ~= 0) then
        return true
    else
        return false
    end
end

function move(v1, v2, v3)
    sim.setJointTargetVelocity(motor1_handle, v1)
    sim.setJointTargetVelocity(motor2_handle, v2)
    sim.setJointTargetVelocity(motor3_handle, v3)
end

function move_to_target(target, ultra)
    


    
        --print(math.deg(alpha), distance, R)
    --A2 and A3
    if (ultra) then --use ultrassonic coordinates
        alpha = math.atan((goal[1] - x), (goal[2] - y))
        print('ultra', math.deg(alpha),(goal[2] - y), (goal[1] - x))
    else
        target_pos = sim.getObjectPosition(target, sim.handle_world)
        midpoint_pos = sim.getObjectPosition(midpoint, sim.handle_world)
    
        alpha = math.atan((target_pos[2] - midpoint_pos[2]), (target_pos[1] - midpoint_pos[1]))
        distance = getDistance(target)
    end
        
        
        if ((alpha > math.rad(30) and alpha <= math.rad(80)) or  (alpha >= math.rad(100) and alpha < math.rad(150)) and not withBall()) then
            approach_point = {target_pos[1], target_pos[2]-(R+10)/100}
            phi = math.atan((approach_point[2] - midpoint_pos[2]), (approach_point[1] - midpoint_pos[1]))

            alpha = phi
        elseif (alpha <= math.rad(-50) and alpha >= math.rad(-130)) then
            approach_point = {target_pos[1]-(R+(1/distance))/100, target_pos[2]}
            phi = math.atan((approach_point[2] - midpoint_pos[2]), (approach_point[1] - midpoint_pos[1]))

            alpha = phi

        elseif ((alpha <= math.rad(30) and alpha >= math.rad(-90)) and not withBall()) then 
            approach_point = {target_pos[1]-(R+(1/(distance*0.5)))/100, target_pos[2]-(R+10)/100}
            phi = math.atan((approach_point[2] - midpoint_pos[2]), (approach_point[1] - midpoint_pos[1]))

            alpha = phi
        elseif ((alpha < math.rad(-90) and alpha >= math.rad(-180)) or (alpha >= math.rad(150)) and not withBall()) then 
            approach_point = {target_pos[1]+(R+(1/distance))/100, target_pos[2]-(R+10)/100}
            phi = math.atan((approach_point[2] - midpoint_pos[2]), (approach_point[1] - midpoint_pos[1]))

            alpha = phi
        end
        
        Vx = math.cos(alpha) * 6
        Vy = math.sin(alpha) * 6
        v1, v2, v3 = inverseKinematics(Vx, Vy, 0)
        move(v1, v2, v3)
        
end

function withBall()
    dist = getDistance(ball)
   -- print(dist)
    if (dist < 0.13) then
        return true
    else
        return false
    end
end

function behavior(distance)
    --withBall()
    if (y < 0.42 and (x < 1.14 and x > 0.34)) then
        movebackward()
    elseif (y > 2.06) then
        moveforward()
    elseif (y < 0.17) then
        movebackward()
    elseif (x > 1.6) then
        turnright()
    elseif (x < 0.19) then
        turnleft()
    elseif (not withBall()) then
        move_to_target(ball)
    elseif (withBall()) then
        print('goal')
       move_to_target(goal, true)
    end
end

function move_around()
    target_pos = sim.getObjectPosition(ball, sim.handle_world)
    midpoint_pos = sim.getObjectPosition(midpoint, sim.handle_world)
    alpha = math.atan((target_pos[2] - midpoint_pos[2]) / (target_pos[1] - midpoint_pos[1]))


    v1, v2, v3 = inverseKinematics(math.cos(alpha), math.sin(alpha), 0)
    move(v1, v2, v3)
end

function sysCall_actuation()
    --dist = getDistance()
    -- move_to_target()
    compassData = { sim.getFloatSignal('compassX'), sim.getFloatSignal('compassY'), sim.getFloatSignal('compassZ') }


    if (x > 0 and y > 0) then
        behavior()
    end
    if (not start) then
        stop()
        start = 0
        print('stop')
    end
    --print(x, y)
    if (compassData[3]) then
        theta = compassData[3]
        if (theta > 0) then
            theta = math.pi - theta
        else
            theta = -(theta + math.pi)
        end
        if (math.abs(theta) >= 0.1) then
            if (v1_ ~= 0 or v2_ ~= 0 or v3_ ~= 0) then
                v1_ = sim.getJointTargetVelocity(motor1_handle)
                v2_ = sim.getJointTargetVelocity(motor2_handle)
                v3_ = sim.getJointTargetVelocity(motor3_handle)
                print('C', v3_)
            end
            correctAngle(theta)
        elseif ((math.abs(theta) <= 0.1) and isSpining()) then
            stop()
            -- print('test')
        end
    end
end

function sysCall_sensing()
    x1 = getDistanceSensor(sonar_x1, max_dist)
    x2 = getDistanceSensor(sonar_x2, max_dist)
    y1 = getDistanceSensor(sonar_y1, max_dist)
    y2 = getDistanceSensor(sonar_y2, max_dist)

    if (x1 > x2) then
        x = x1
    else
        x = max_x - D - x2
    end
    if (y1 > y2) then
        val_y = y1
    else
        val_y = max_y - D - y2
    end

    if (x >= 0.41 and x <= 1.1) then
        y = val_y + 0.04
    else
        y = val_y
    end
end

function sysCall_init()
    ui             = simUI.create(
    '<ui enabled="true" modal="false" title="Omniwheel" layout="vbox" placement="relative" position="20,20">' .. [[
         <button enabled="true" text="Forward" on-click="moveforward"></button>
         <button enabled="true" text="Backward" on-click="movebackward"></button>
         <button enabled="true" text="Left" on-click="turnleft"></button>
         <button enabled="true" text="right" on-click="turnright"></button>
         <button enabled="true" text="rotleft" on-click="rotleft"></button>
         <button enabled="true" text="rotright" on-click="rotright"></button>
         <button enabled="true" text="diagonalLF" on-click="diagonalLF"></button>
         <button enabled="true" text="diagonalRT" on-click="diagonalRT"></button>
         <button enabled="true" text="Target" on-click="move_to_target(ball)"></button>
         <button enabled="true" text="MoveAround" on-click="move_around"></button>
         <button enabled="true" text="Stop" on-click="stop"/>
         </ui>]])

    x1, x2, y1, y2 = 0, 0, 0, 0
    x, y           = 0, 0
    v1, v2, v3     = 0, 0, 0
    v1_, v2_, v3_  = 0, 0, 0
    max_x, max_y   = 1.82, 2.43
    gyroData       = { 0, 0, 0 }
    initial_angle  = math.pi
    --Distance Sensors (Ultrassonic)
    sonar_x1       = sim.getObject('/Sensor_x1')
    sonar_x2       = sim.getObject('/Sensor_x2')
    sonar_y1       = sim.getObject('/Sensor_y1')
    sonar_y2       = sim.getObject('/Sensor_y2')
    max_dist       = 1
    --Get distance
    L              = 0.764 --Distance between robot's wheel center
    D              = 0.20 --Diameter of the robot
    R = 14

    motor1_handle  = sim.getObject('/motor1')
    motor2_handle  = sim.getObject('/motor2')
    motor3_handle  = sim.getObject('/motor3')
    midpoint       = sim.getObject('/Midpoint')
    ball           = sim.getObject('/ball')
   -- goal           = sim.getObject('/goal')
    goal           = {0.85, 0.28}




    wheel1_handle = sim.getObject('/wheel1')
    wheel2_handle = sim.getObject('/wheel2')
    wheel3_handle = sim.getObject('/wheel3')
end