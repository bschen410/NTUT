#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PI 3.14
#define ShapeText(TYPE)                \
    char name[10];                     \
    double (*perimeter)(struct TYPE*); \
    double (*area)(struct TYPE*)

// Base shape struct
typedef struct shape_s {
    ShapeText(shape_s);
} shape_t;

// Circle
typedef struct circle_s {
    ShapeText(circle_s);
    double radius;
} circle_t;

// Rectangle
typedef struct rectangle_s {
    ShapeText(rectangle_s);
    double length;
    double width;
} rectangle_t;

// Square
typedef struct square_s {
    ShapeText(square_s);
    double edge;
} square_t;

// Triangle
typedef struct triangle_s {
    ShapeText(triangle_s);
    double a, b, c;
} triangle_t;

// Function implementations

double circle_perimeter(circle_t* c) {
    return 2 * PI * c->radius;
}
double circle_area(circle_t* c) {
    return PI * c->radius * c->radius;
}

double rectangle_perimeter(rectangle_t* r) {
    return 2 * (r->length + r->width);
}
double rectangle_area(rectangle_t* r) {
    return r->length * r->width;
}

double square_perimeter(square_t* s) {
    return 4 * s->edge;
}
double square_area(square_t* s) {
    return s->edge * s->edge;
}

double triangle_perimeter(triangle_t* t) {
    return t->a + t->b + t->c;
}
double triangle_area(triangle_t* t) {
    double p = (t->a + t->b + t->c) / 2;
    return sqrt(p * (p - t->a) * (p - t->b) * (p - t->c));
}

int main() {
    int n;
    scanf(" %d", &n);

    double totalPerimeter = 0, totalArea = 0;

    while (n--) {
        char type;
        scanf(" %c", &type);

        if (type == 'C') {
            circle_t* c = malloc(sizeof(circle_t));
            scanf("%lf", &c->radius);
            strcpy(c->name, "Circle");
            c->perimeter = circle_perimeter;
            c->area = circle_area;
            double p = c->perimeter(c);
            double a = c->area(c);
            totalPerimeter += p;
            totalArea += a;
            printf("%.2f %.2f\n", p, a);
            free(c);
        } else if (type == 'R') {
            rectangle_t* r = malloc(sizeof(rectangle_t));
            scanf("%lf %lf", &r->length, &r->width);
            strcpy(r->name, "Rectangle");
            r->perimeter = rectangle_perimeter;
            r->area = rectangle_area;
            double p = r->perimeter(r);
            double a = r->area(r);
            totalPerimeter += p;
            totalArea += a;
            printf("%.2f %.2f\n", p, a);
            free(r);
        } else if (type == 'S') {
            square_t* s = malloc(sizeof(square_t));
            scanf("%lf", &s->edge);
            strcpy(s->name, "Square");
            s->perimeter = square_perimeter;
            s->area = square_area;
            double p = s->perimeter(s);
            double a = s->area(s);
            totalPerimeter += p;
            totalArea += a;
            printf("%.2f %.2f\n", p, a);
            free(s);
        } else if (type == 'T') {
            triangle_t* t = malloc(sizeof(triangle_t));
            scanf("%lf %lf %lf", &t->a, &t->b, &t->c);
            strcpy(t->name, "Triangle");
            t->perimeter = triangle_perimeter;
            t->area = triangle_area;
            double p = t->perimeter(t);
            double a = t->area(t);
            totalPerimeter += p;
            totalArea += a;
            printf("%.2f %.2f\n", p, a);
            free(t);
        }
    }

    // 印出總和
    printf("%.2f %.2f\n", totalPerimeter, totalArea);
    return 0;
}
