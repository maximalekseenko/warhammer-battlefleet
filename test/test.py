import pygame
import math

# CONSTANTS -- VISUAL
POINT_WIDTH = 5
SCREEN_WIDTH = 640
SCREEN_HEIGHT = 480
VECTOR_LEN = 35



start_point = (SCREEN_WIDTH * 1/2, SCREEN_HEIGHT * 1/2)
start_angle = math.pi / 2
end_point = (0,0)

path_len = 5
path_points = []


path_distance_min = 50
path_distance_max = 100
path_angle_max = math.pi/2

add_to_log = {}
def To_Log():
    _ret = {
        "start_point":start_point,
        "start_angle":start_angle,
        "path_distance_min": path_distance_min,
        "path_distance_max": path_distance_max,
        "path_angle_max":path_angle_max,
        "points": list(map(lambda _l: f"({round(_l[0][0])},{round(_l[0][1])}):{round(_l[1], 2)}",path_points)),
    }
    _ret.update(add_to_log)
    return _ret


def Make_Path():
    path_points.clear()


    # /ALL CALCULATIONS DONE RELATIVE TO STARTING POINT\
    # relative target point (p, q) = (x1 - x2, y1 - y2)
    _p = end_point[0] - start_point[0]
    _q = end_point[1] - start_point[1]

    # find a and b for line, parallel to vessel
    # line: ax + by = 0
    _a = math.sin(start_angle + math.pi / 2)
    _b = math.cos(start_angle + math.pi / 2)


    # [check for curve here]
    if _b * _p == _a * _q:
        return

    # find center of rotation circle (path)
    # t = (p^2 + q^2) / (2bp - 2aq)  node:formula came from fact, 
    #                                     that distance form CenterPoint to StartPoint ==
    #                                     == distance form CenterPoint to EndPoint == radius
    _t = (_p * _p + _q * _q) / (2 * _b * _p - 2 * _a * _q)

    # path is a circular curve with center point at point O: (bt, -at)
    _o = (_b * _t, -_a * _t)

    # with radius = √((bt)^2 + (-at)^2)
    _r = math.sqrt((_b * _t) * (_b * _t) + (_a * _t) * (_a * _t))

    # find path angle and distance
    _angA = math.atan2(_p-_o[0], _q-_o[1])
    _angB = math.atan2(-_o[0], -_o[1])
    _path_angle = (_angA - _angB) % (2*math.pi)
    if _angB < 0: _path_angle = _path_angle - 2*math.pi

    _path_distance = abs(_path_angle * _r)
    # \ALL CALCULATIONS DONE RELATIVE TO STARTING POINT/

    # actual center
    _center = (_o[0] + start_point[0], _o[1] + start_point[1])

    # /DELETE\
    add_to_log["ACen"] = _center[0], _center[1]
    add_to_log["pDist"] = _path_distance
    add_to_log["angA"] = _angA
    add_to_log["angB"] = _angB
    # add_to_log["pAng1"] = _path_angle1
    # add_to_log["pAng2"] = _path_angle2
    add_to_log["pAng"] = _path_angle
    add_to_log["rad"] = _r
    # \DELETE/


    # [checks go here]

    _step_angle = _path_angle / path_len
    _cur_angle = start_angle
    _point_angle = math.atan2(-_o[1], -_o[0])
    _cur_point = (start_point[0], start_point[1])

    for _i in range(path_len):

        # turn current point
        _point_angle -= _step_angle
        _cur_angle += _step_angle

        # move current point
        _cur_point = (
            _center[0] + math.cos(_point_angle) * _r,
            _center[1] + math.sin(_point_angle) * _r
        )

        # add to list
        path_points.append(((_cur_point[0], _cur_point[1]), _cur_angle))



def Render():
    screen.fill('#777777')

    # start point
    pygame.draw.circle(screen, "#aa0000", start_point, POINT_WIDTH)
    pygame.draw.line(screen, "#aa0000", start_point, (
        start_point[0] + math.cos(start_angle) * VECTOR_LEN,
        start_point[1] + -math.sin(start_angle) * VECTOR_LEN, 
    ))

    # ENDPOINT
    pygame.draw.circle(screen, "#00aa00", end_point, POINT_WIDTH)

    _to_log = To_Log()
    _color = "#0000aa" if (
        path_distance_min <= _to_log["pDist"] <= path_distance_max and
        abs(_to_log["pAng"]) < path_angle_max
    ) else "#aa0000"
    for _point, _angle in path_points:
        pygame.draw.circle(screen, _color, _point, POINT_WIDTH / 2)
        pygame.draw.line(screen, _color, _point, (
            _point[0] + math.cos(_angle) * VECTOR_LEN,
            _point[1] + -math.sin(_angle) * VECTOR_LEN, 
        ))

    
    _log_text_offset = 0
    _to_log = To_Log()
    for _log_text, _log_value in _to_log.items():
        _text_surface = font.render(f"{_log_text}: {_log_value}", 0, "#aaaaaa", "#000000")
        _text_rect = _text_surface.get_rect()
        screen.blit(_text_surface, (0, _log_text_offset))
        _log_text_offset += _text_rect.height

    pygame.draw.circle(screen, "#aaaaaa", _to_log["ACen"], POINT_WIDTH)

    pygame.draw.circle(screen, "#aaaaaa", _to_log["ACen"], _to_log["rad"],1)


# run
pygame.init()
clock = pygame.time.Clock()
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT), pygame.RESIZABLE)
is_running = True
font = pygame.font.Font(None, 20)

Make_Path()

while is_running:
    clock.tick(60)

    # handle
    for event in pygame.event.get():
        
        if event.type == pygame.QUIT:
            is_running = False

        elif event.type == pygame.MOUSEMOTION:
            end_point = event.pos

        elif event.type == pygame.MOUSEBUTTONUP:
            if event.button == 1:
                start_angle = math.atan2(end_point[0] - start_point[0], end_point[1] - start_point[1]) - math.pi/2
        # elif event.type == pygame.KEYUP:
        #     if event.key == pygame.K_UP: v_cur += 1
        #     if event.key == pygame.K_DOWN: v_cur -= 1
        #     if event.key == pygame.K_RIGHT: a_cur += 1
        #     if event.key == pygame.K_LEFT: a_cur -= 1

        else: print(event)

    Make_Path()
    # render
    Render()

    pygame.display.update()
pygame.quit()