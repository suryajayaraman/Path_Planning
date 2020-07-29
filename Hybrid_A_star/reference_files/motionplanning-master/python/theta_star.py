#!/usr/bin/env python2
# -*- coding: utf-8 -*-

from mapinfo import MapInfo
from scipy.spatial import cKDTree
import math

def distance(p1, p2):
    return math.sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)

def find_min_f(l, f_score):
    r = min(l, key=lambda item: f_score[item])
    i = l.index(r)
    return i

def neighbor_nodes(x, roadmap):
    plist = [(x[0] - 1, x[1] - 1), (x[0] - 1, x[1]), (x[0] - 1, x[1] + 1), (x[0], x[1] + 1), (x[0] + 1, x[1] + 1), (x[0] + 1, x[1]), (x[0] + 1, x[1] - 1), (x[0], x[1] - 1)]
    for p in plist:
        if 0 < p[0] < roadmap.width and 0 < p[1] < roadmap.height and p not in roadmap.obstacle:
            yield p

def reconstruct_path(camefrom, current_node):
    if current_node in camefrom:
        p = reconstruct_path(camefrom, camefrom[current_node])
        return p + [current_node]
    else:
        return [current_node]

def middle_point(p1, p2):
    x1 = float(p1[0])
    y1 = float(p1[1])
    x2 = float(p2[0])
    y2 = float(p2[1])
    return ((x1+x2)/2, (y1+y2)/2)

def line_of_sight(p1, p2, okdtree):
    points = [p1, p2]
    L = distance(p1, p2)
    # generate points in line p1-p2, make sure number of points more than distance p1 to p2
    while len(points) < L*1.3:
        i = 0
        j = 1
        while j < len(points):
            points.insert(j, middle_point(points[i], points[j]))
            i += 2
            j += 2
    # judge each point collide obstacle or not
    for p in points:
        d, _ = okdtree.query(p)
        if d < 1.0:
            return False
    return True

def a_star_planning(map_info, display=False):
    closedlist = []
    openlist = []
    camefrom = dict()
    g_score = {map_info.start: 0}
    h_score = {map_info.start: distance(map_info.start, map_info.end)}
    f_score = {map_info.start: h_score[map_info.start]}
    openlist.append(map_info.start)
    okdtree = cKDTree(map_info.obstacle)
    while openlist:
        min_i = find_min_f(openlist, f_score)
        x = openlist.pop(min_i)
        if x == map_info.end:
            return reconstruct_path(camefrom, map_info.end)
        closedlist.append(x)
        if display:
            map_info.close = x
        for y in neighbor_nodes(x, map_info):
            if y in closedlist:
                continue
            tentative_g_score = g_score[x] + distance(x, y)
            if y not in openlist:
                tentative_is_better = True
            elif tentative_g_score < g_score[y]:
                tentative_is_better = True
            else:
                tentative_is_better = False
            if tentative_is_better:
                if x != map_info.start and line_of_sight(y, camefrom[x], okdtree):
                    camefrom[y] = camefrom[x]
                    g_score[y] = g_score[camefrom[x]] + distance(camefrom[x], y)
                    h_score[y] = distance(y, map_info.end)
                    f_score[y] = g_score[y] + h_score[y]
                else:
                    camefrom[y] = x
                    g_score[y] = tentative_g_score
                    h_score[y] = distance(y, map_info.end)
                    f_score[y] = g_score[y] + h_score[y]
                openlist.append(y)
                if display:
                    map_info.open = y
    return []

if __name__ == "__main__":
    m = MapInfo(60, 40)
    m.show()
    m.start = (10, 10)
    m.end = (50, 30)
    m.obstacle = [(20, i) for i in range(30)] + [(40, 40 - i) for i in range(30)]
    raw_input('enter to start ...')
    m.path = a_star_planning(m, display=True)
    m.wait_close()