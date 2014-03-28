/*
ID: yuguess1
LANG: C
TASK: castle 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int **maze;
int maze_length;
int maze_width;

print_maze(width, length) {
    int i,j;
    for (i = 0; i < width  * 2 + 1; i++) {
        for (j = 0; j < length * 2 + 1; j++) {
            printf("%3d", maze[i][j]);
        }
        printf("\n");
    }
}

build_maze(int length, int width, int data) {
    
    int maze_i = width * 2 + 1;
    int maze_j = length * 2 + 1;
    int k, m;
        
    maze[maze_i][maze_j] = 0;

    int west = data & 0x1;
    if (west == 1) {
        maze[maze_i][maze_j - 1] = -1;
    } else {
        maze[maze_i][maze_j - 1] = -2;
    }

    int north = data & 0x2;
    if (north == 2) {
        maze[maze_i - 1][maze_j] = -1;
    } else {
        maze[maze_i - 1][maze_j] = -2;
    }

    int east = data & 0x4;
    if (east == 4) {
        maze[maze_i][maze_j + 1] = -1;
    } else {
        maze[maze_i][maze_j + 1] = -2;
    }

    int south = data & 0x8;
    if (south == 8) {
        maze[maze_i + 1][maze_j] = -1;
    } else {
        maze[maze_i + 1][maze_j] = -2;
    }
}

void depth_first_search(int maze_i, int maze_j, int area_mark) {
    if (maze[maze_i][maze_j] != 0)
        return;
    else
        maze[maze_i][maze_j] = area_mark; 

    if (maze[maze_i - 1][maze_j] != -1)
        depth_first_search(maze_i - 2, maze_j, area_mark);

    if (maze[maze_i][maze_j - 1] != -1)
        depth_first_search(maze_i, maze_j - 2, area_mark);

    if (maze[maze_i][maze_j + 1] != -1)
        depth_first_search(maze_i, maze_j + 2, area_mark);

    if (maze[maze_i + 1][maze_j] != -1)
        depth_first_search(maze_i + 2, maze_j, area_mark);

    return; 
}

int mark_connected_area(int length, int width, int area_mark) {
    int maze_i = width * 2 + 1;
    int maze_j = length * 2 + 1;
    if (maze[maze_i][maze_j] == 0) {
        depth_first_search(maze_i, maze_j, area_mark); 
        return 1;
    } else {
        return 0;
    }
}

int is_optimal_wall(int i, int j, int *area_histogram, int *flag) {
    int horizon_connect_area = 0;
    int vertical_connect_area = 0; 
    if (maze[i + 1][j] > 0 && maze[i - 1][j] > 0 && maze[i + 1][j] != maze[i - 1][j])
        vertical_connect_area = area_histogram[maze[i + 1][j] - 1] + area_histogram[maze[i - 1][j] - 1];

    if (maze[i][j - 1] > 0 && maze[i][j + 1] > 0 && maze[i][j - 1] != maze[i][j + 1])
        horizon_connect_area = area_histogram[maze[i][j + 1] - 1] + area_histogram[maze[i][j - 1] - 1];

    if (horizon_connect_area > vertical_connect_area) {
        *flag = 0;
        return horizon_connect_area;
    } else {
        *flag = 1;
        return vertical_connect_area;
    }
}

int main () {
    int width;
    int length;
    int i, j;
    int temp;

    FILE *fin = fopen("castle.in", "r");
    FILE *fout = fopen("castle.out", "w");

    fscanf(fin, "%d", &length);
    fscanf(fin, "%d", &width);

    maze_length = 2 * length + 1;
    maze_width = 2 * width + 1;
    
    int area_count = 0;
    int *area_histogram;
    int max_connected_area = 0;
    int remove_max_connected_area = 0;
    int temp_connected_area = 0;
    int optimal_i, optimal_j;

    if ((maze = (int **)malloc(maze_width * sizeof(int *))) == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }

    for (i = 0; i < maze_width; i++) {
        if ((maze[i] = (int *)malloc(maze_length * sizeof(int))) == NULL) {
            fprintf(stderr, "malloc error\n");
            exit(1);
        }
        memset(maze[i], -1, maze_length * sizeof(int));
    }

    for (j = 0; j < width; ++j) {
        for (i = 0; i < length; i++) {
            fscanf(fin, "%d", &temp);
            build_maze(i, j, temp);
        }
    }
    //print_maze();
    for (j = 0; j < width; ++j) {
        for (i = 0; i < length; i++) {
            if (mark_connected_area(i, j, area_count + 1) == 1)
                area_count++;
        }
    }
    //print_maze();
    //printf("area:%d\n", area_count);
    if ((area_histogram = (int *)malloc((area_count) * sizeof(int))) == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }

    for (i = 0; i < maze_width; i++)
        for (j = 0; j < maze_length; j++) {
            if (maze[i][j] > 0) {
                area_histogram[maze[i][j] - 1]++;
            }
        }

    for (i = 0; i < area_count; i++) {
        //printf("%d:%d\n", i + 1, area_histogram[i]);
        if (area_histogram[i] > max_connected_area) {
            max_connected_area = area_histogram[i];
        }
    }

    int flag = 0;
    int orientation = 0;
    for (j = 1; j < maze_length - 1; j++)   
        for (i = maze_width - 2; i > 0; i--) {
            if (maze[i][j] == -1) {
                if ((temp_connected_area = is_optimal_wall(i, j, area_histogram, &flag)) != 0) {
                    if (temp_connected_area > remove_max_connected_area) {
                        remove_max_connected_area =  temp_connected_area;
                        optimal_i = i;
                        optimal_j = j;
                        orientation = flag;
                    }
                }
            }
        }
     
    fprintf(fout, "%d\n", area_count);
    fprintf(fout, "%d\n", max_connected_area);
    fprintf(fout, "%d\n", remove_max_connected_area);
    
    if (orientation == 0) { 
        fprintf(fout, "%d %d", (optimal_i - 1) / 2 + 1, (optimal_j - 1) / 2 + 1);
        fprintf(fout, " E\n");
    } else { 
        fprintf(fout, "%d %d", (optimal_i + 1) / 2 + 1, (optimal_j - 1) / 2 + 1);
        fprintf(fout, " N\n");
    }

    free(area_histogram);
    for (i = 0; i < maze_width; i++) {
        free(maze[i]);
    }
    free(maze);
    fclose(fin);
    fclose(fout);
}
