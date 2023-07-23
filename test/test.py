import pygame
import math

# CONSTANTS -- VISUAL
POINT_WIDTH = 5
SCREEN_WIDTH = 640
SCREEN_HEIGHT = 480
VECTOR_LEN = 35



start_point = (SCREEN_WIDTH * 1/5, SCREEN_HEIGHT * 2/4)
start_angle = 0#math.pi / 4
end_point = (0, 0)

path_len = 5
path_points = []


v_min = 20
v_max = 100
v_cur = 30

a_min = -10
a_max = 10
a_cur = 5

def To_Log():
    return {
        "start_point":start_point,
        "start_angle":start_angle,
        "v_cur": v_cur,
        "a_cur": a_cur,
        "atan":math.atan2(
            +math.sin(start_angle) * v_cur + -math.cos(start_angle) * a_cur,
            +math.cos(start_angle) * v_cur + -math.sin(start_angle) * a_cur,
        ),
        "atan2":math.atan2(
            v_cur,
            -a_cur,
        ),
        "c":math.cos(start_angle),
        "s":math.sin(start_angle),
        "points": list(map(lambda _l: f"({round(_l[0][0])},{round(_l[0][1])}):{round(_l[1], 2)}",path_points)),
    }


def Make_Path():
    path_points.clear()

    # v_cur = (end_point[0] - start_point[0]) / path_len
    # a_cur = (end_point[1] - start_point[1]) / path_len
    # aaa

    # bbb


    _cur_point = start_point
    _cur_angle = start_angle


    for _i in range(path_len):

        # turn current point
        _cur_angle += math.atan2( -a_cur, +v_cur)

        # move current point
        _cur_point = (
            _cur_point[0] + +math.cos(_cur_angle) * v_cur + +math.sin(_cur_angle) * a_cur,
            _cur_point[1] + -math.sin(_cur_angle) * v_cur + +math.cos(_cur_angle) * a_cur
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

    for _point, _angle in path_points:
        pygame.draw.circle(screen, "#0000aa", _point, POINT_WIDTH / 2)
        pygame.draw.line(screen, "#0000aa", _point, (
            _point[0] + math.cos(_angle) * VECTOR_LEN,
            _point[1] + -math.sin(_angle) * VECTOR_LEN, 
        ))

    
    _log_text_offset = 0
    for _log_text, _log_value in To_Log().items():
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

while is_running:
    clock.tick(60)

    # handle
    for event in pygame.event.get():
        
        if event.type == pygame.QUIT:
            is_running = False

        elif event.type == pygame.MOUSEMOTION:
            end_point = event.pos
            Make_Path()

        elif event.type == pygame.KEYUP:
            if event.key == pygame.K_UP: v_cur += 1
            if event.key == pygame.K_DOWN: v_cur -= 1
            if event.key == pygame.K_RIGHT: a_cur += 1
            if event.key == pygame.K_LEFT: a_cur -= 1

        else: print(event)

    # render
    Render()

    pygame.display.update()
pygame.quit()