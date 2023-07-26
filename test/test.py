import pygame
import math

# CONSTANTS -- VISUAL
POINT_WIDTH = 5
SCREEN_WIDTH = 640
SCREEN_HEIGHT = 480
VECTOR_LEN = 35
DIFF = 0.001



start_point = (SCREEN_WIDTH * 1/2, SCREEN_HEIGHT * 1/2)
start_angle = math.pi / 2
end_point = (0,0)

path_len = 5
path_points = []
path_legal = False
path_center = [0,0]


path_distance_min = 20
path_distance_max = 30
path_angle_max = math.pi/5

add_to_log = {}
def To_Log():
    _ret = {
        # "start_point":start_point,
        # "start_angle":start_angle,
        # "path_distance_min": path_distance_min,
        # "path_distance_max": path_distance_max,
        # "path_angle_max":path_angle_max,
        # "points": list(map(lambda _l: f"({round(_l[0][0])},{round(_l[0][1])}):{round(_l[1], 2)}",path_points)),
    }
    _ret.update(add_to_log)
    return _ret


def _Make_Path_Line(_p, _q, _a, _b):

    # get path distance
    _path_distance = math.dist(start_point, end_point)

    # make path points by moving _cur_point forward
    _distance_by_step = _path_distance / path_len
    _vessel_angle = start_angle
    # if abs((_vessel_angle - math.atan2(_p, _q)) % math.pi) >= DIFF:
    #     _vessel_angle = -_vessel_angle
    _cur_point = (start_point[0], start_point[1])

    path_points.clear()
    for _i in range(path_len):

        # move current point
        _cur_point = (
            _cur_point[0] + math.cos(_vessel_angle) * _distance_by_step,
            _cur_point[1] + math.sin(_vessel_angle) * _distance_by_step
        )

        # add to list
        path_points.append(((_cur_point[0], _cur_point[1]), _vessel_angle))

    # check if points are valid
    global path_legal
    path_legal = True
    if _distance_by_step < path_distance_min: path_legal = False
    if _distance_by_step > path_distance_max: path_legal = False

def _Make_path_Curve(_p, _q, _a, _b):
    # find center of rotation circle (path)
    # t = (p^2 + q^2) / (2bp - 2aq)  node:formula came from fact, 
    #                                     that distance form CenterPoint to StartPoint ==
    #                                     == distance form CenterPoint to EndPoint == radius
    _t = (_p * _p + _q * _q) / (2 * _b * _p - 2 * _a * _q)
    # path is a circular curve with center point at point O: (bt, -at)
    _o = (_b * _t, -_a * _t)
    # with radius = √((Ox-0)^2 + (Oy-0)^2)
    _radius = math.dist((0,0), _o)

    # find path angle and distance
    # get angle from center to start_point(A) and end_point(B)
    _angA = math.atan2(_p-_o[0], _q-_o[1])
    _angB = math.atan2(-_o[0], -_o[1])
    # get angle
    _path_angle = (_angA - _angB) % (2*math.pi)

    add_to_log["ab"] = (_a,_b)
    add_to_log["angA"] = _angA
    add_to_log["angB"] = _angB
    add_to_log["ang"]  = _path_angle
    # fix angle for clockwise movement
    if (_angB < 0) == (_b < 0): 
        _path_angle = _path_angle - 2*math.pi

    # get path distance
    _path_distance = abs(_path_angle * _radius)
    # \ALL CALCULATIONS DONE RELATIVE TO STARTING POINT/

    # actual center
    path_center[0] = _o[0] + start_point[0]
    path_center[1] = _o[1] + start_point[1]

    # make path points by modifing _cur_angle (angle between center and vessel)
    _angle_by_step = _path_angle / path_len
    _distance_by_step = _path_distance / path_len
    _vessel_angle = start_angle
    _cur_angle = math.atan2(-_o[1], -_o[0])
    _cur_point = (start_point[0], start_point[1])

    path_points.clear()
    for _i in range(path_len):

        # turn current point
        _cur_angle -= _angle_by_step
        _vessel_angle += _angle_by_step

        # move current point
        _cur_point = (
            path_center[0] + math.cos(_cur_angle) * _radius,
            path_center[1] + math.sin(_cur_angle) * _radius
        )

        # add to list
        path_points.append(((_cur_point[0], _cur_point[1]), _vessel_angle))

    # check if points are valid
    global path_legal
    path_legal = True
    if abs(_angle_by_step) > path_angle_max: path_legal = False
    if _distance_by_step < path_distance_min: path_legal = False
    if _distance_by_step > path_distance_max: path_legal = False

def Make_Path():
    # /ALL CALCULATIONS DONE RELATIVE TO STARTING POINT\
    # relative target point (p, q) = (x1 - x2, y1 - y2)
    _p = end_point[0] - start_point[0]
    _q = end_point[1] - start_point[1]
    # find a and b for line(ax + by = 0), parallel to vessel
    _a = math.sin(start_angle + math.pi / 2)
    _b = math.cos(start_angle + math.pi / 2)
    # 
    if abs(_b * _p - _a * _q) < DIFF: _Make_Path_Line(_p, _q, _a, _b)
    else: _Make_path_Curve(_p, _q, _a, _b)


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
    _color = "#0000aa" if path_legal else "#aa0000"
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