import numpy as np
import matplotlib.pyplot as plt
import math 
from scipy.spatial import ConvexHull

triangles = []

def draw_triangle(triangle, color='black'):
    plt.plot([triangle[0][0], triangle[1][0]], [triangle[0][1], triangle[1][1]], '-', color=color)
    plt.plot([triangle[1][0], triangle[2][0]], [triangle[1][1], triangle[2][1]], '-', color=color)
    plt.plot([triangle[2][0], triangle[0][0]], [triangle[2][1], triangle[0][1]], '-', color=color)

def create_super_triangle():
    global triangles
    # rectangle that encloses all the points
    min_x = min(points[:, 0])
    max_x = max(points[:, 0])
    min_y = min(points[:, 1])
    max_y = max(points[:, 1])

    rect_base = max_x - min_x
    rect_height = max_y - min_y
    origin_x = min_x + rect_base/2
    origin_y = min_y
    offset = 0.02

    p1 = np.array([origin_x - rect_base - offset, origin_y - offset])
    p2 = np.array([origin_x + rect_base + offset, origin_y - offset])
    p3 = np.array([origin_x, origin_y + 2 * rect_height + offset])
    super_triangle = np.array([p1, p2, p3, 1])
    triangles.append(super_triangle)
    
def distance_between_two_points(p1, p2):
    dx = (p1[0] - p2[0])
    dy = (p1[1] - p2[1])
    return math.sqrt(dx*dx + dy*dy)

def find_circum_centre(triangle):
    
    delta_bc_y = (triangle[1][1] - triangle[2][1])
    delta_ca_y = (triangle[2][1] - triangle[0][1])
    delta_ab_y = (triangle[0][1] - triangle[1][1])
    delta_cb_x = (triangle[2][0] - triangle[1][0])
    delta_ac_x = (triangle[0][0] - triangle[2][0])
    delta_ba_x = (triangle[1][0] - triangle[0][0])

    a_len_sqr = (triangle[0][0] * triangle[0][0] + triangle[0][1] * triangle[0][1])
    b_len_sqr = (triangle[1][0] * triangle[1][0] + triangle[1][1] * triangle[1][1])
    c_len_sqr = (triangle[2][0] * triangle[2][0] + triangle[2][1] * triangle[2][1])
    x = y = 0
    d = 2 * (triangle[0][0] * delta_bc_y + triangle[1][0] * delta_ca_y + triangle[2][0] * delta_ab_y)

    if(math.fabs(d) < 0.0000000001):
        print("bad d: " + str(triangle[0][0]) + " " + str(delta_bc_y) + " " + str(triangle[1][0]) + " " + str(delta_ca_y) + " " + str(triangle[2][0]) + " " + str(delta_ab_y))
        return 0.0, 0.0
    
    x = (a_len_sqr*delta_bc_y + b_len_sqr*delta_ca_y + c_len_sqr*delta_ab_y) / d
    y = (a_len_sqr*delta_cb_x + b_len_sqr*delta_ac_x + c_len_sqr*delta_ba_x) / d
    return x, y

def point_within_triangle_circumcircle(point, triangle):
    circumcentre = find_circum_centre(triangle)
    circumradius = distance_between_two_points(triangle[0], circumcentre)
    is_point_within_circumcircle = distance_between_two_points(point, circumcentre) < circumradius
    return is_point_within_circumcircle

def debug_triangle(triangle):
    draw_triangle(triangle, 'red')
    circumcentre = find_circum_centre(triangle)
    plt.plot(circumcentre[0], circumcentre[1], 'ko')
    circumradius = distance_between_two_points(triangle[0], circumcentre)
    draw_circle(circumcentre[0], circumcentre[1], circumradius, 'orange')

def draw_circle(x, y, radius, color='black'):
    theta = np.linspace( 0 , 2 * np.pi , 150 )
    a = radius * np.cos( theta ) + x
    b = radius * np.sin( theta ) + y
    plt.plot( a, b, color=color)

# Generate random points (you can replace this with your own point data)
np.random.seed(0)
points = np.random.rand(6, 2)  # Generates 30 random 2D points
plt.plot(points[:,0], points[:,1], 'o')

# Compute the convex hull
hull = ConvexHull(points)
# Plot the convex hull
for simplex in hull.simplices:
    plt.plot(points[simplex, 0], points[simplex, 1], 'k-')

create_super_triangle()

# while invalid triangles exist, do algorithm:
for point_index in range(len(points)):
    # loop through all triangles
    for triangle_index in range(len(triangles)):
        triangle = triangles[triangle_index]
        if(triangle[3] == 0):
            continue

        if (point_within_triangle_circumcircle(points[point_index], triangle)):
            triangles[triangle_index][3] = 0
        
        # form 3 new triangles
        triangles.append(np.array([triangle[0], points[point_index], triangle[2], 1]))
        triangles.append(np.array([triangle[0], triangle[1], points[point_index], 1]))
        triangles.append(np.array([triangle[1], triangle[2], points[point_index], 1]))

## finally, remove any triangles that share two or more vertices with the super triangle
#for triangle_index in range(1, len(triangles)):
#    for i in range(3):
#        if (triangles[triangle_index][3] == 0):
#            break
#        for j in range(3):
#            if distance_between_two_points(triangles[triangle_index][i], triangles[0][j]) < 0.000001:
#                triangles[triangle_index][3] = 0
#                break

for triangle_index in range(len(triangles)):
    if (triangles[triangle_index][3] == 1):
        draw_triangle(triangles[triangle_index])


#for point in points:
#    debug_triangle(np.array([triangles[0][0], point, triangles[0][2]]))
#    debug_triangle(np.array([triangles[0][0], triangles[0][1], point]))
#    debug_triangle(np.array([triangles[0][1], triangles[0][2], point]))

# Connect the last point to the first point to close the hull
plt.plot(points[hull.vertices[0], 0], points[hull.vertices[0], 1], 'k-')

plt.axis('equal')
plt.show()
 
