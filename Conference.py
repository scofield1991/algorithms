import operator


#with open('/home/alex/Algorithms/tc/1.in') as f: 
#    content = f.readlines()

#content = [x.strip() for x in content]

#print (content)

num_cases = input()
for i in range(num_cases):
    num_programs = input()
    programs = []
    times = []

    for prog in range(num_programs):
        #program_time = input()
        start_hour, start_minute, end_hour, end_minute = raw_input().split() 

        times.append({'start': int(start_hour) * 60 + int(start_minute), 'end': int(end_hour) * 60 + int(end_minute) })


    #print (times)
#times = [{'start': 12 * 60 + 10, 'end': 16 * 60 + 20}, {'start': 9 * 60, 'end': 13 * 60},
#         {'start': 11 * 60, 'end': 18 * 60}, {'start': 13 * 60, 'end': 15 * 60 + 30},
#         {'start': 14 * 60 + 30, 'end': 16 * 60 + 30}, {'start': 16 * 60 + 30, 'end': 18 * 60},
#         {'start': 18 * 60, 'end': 19 * 60}] 



times.sort(key=operator.itemgetter('start'))
adj_lists = [[] for time in times]


for i, time in enumerate(times):
    print(time)
    for j in range(i+1, len(times)):
        if times[j]['start'] >= time['end'] or times[j]['end'] <= time['start']:
            adj_lists[i].append(j)

print (adj_lists)


def dfs_util(v, visited):
    sums = []
    max_sum = 0
    time = times[v]['end'] - times[v]['start']
    visited[v] = True
    
    for adj in adj_lists[v]:
        if not visited[adj]:
            sm =  dfs_util(adj, visited)
            sums.append(sm)
        
    if len(sums) > 0:
        max_sum = max(sums)
    
    return time + max_sum



def isAdjacent(v, parent):
    time_parent = times[parent]
    time_v = times[v]

    if time_v['start'] >= time_parent['end']:
        return True

    return False

def all_visited(visited):
    for visit in visited:
        if visit == False:
            return False

    return True


def get_times_old(visited, times, parent_1 = -1, parent_2 = -1):

    sum_time = 0
    max_time = 0


    for i in range(len(times)):
        #visited = [False for time in times]
        if(parent_1 == -1 or isAdjacent(i, parent_1)) and not visited[i]:
            print (i, "adjacent to ", parent_1)
            time_person_1 = times[i]
            parent_1 = i
            visited[i] = True
            sum_time += time_person_1['end'] - time_person_1['start']

            for j in range(i+1, len(times)):
                if(parent_2 == -1 or isAdjacent(j, parent_2)) and not visited[j]:
                    print (j, "adjacent to ", parent_2)
                    time_person_2 = times[j]
                    parent_2 = j
                    visited[j] = True

                    sum_time += time_person_2['end'] - time_person_2['start']

                    if not all_visited(visited):
                        sum_time += get_times(visited, times, parent_1, parent_2)


                    if sum_time > max_time:
                        max_time = sum_time
    print (max_time)
    print (parent_1)
    return max_time 

total_times = []
visited = [False for time in times]

#max_time = get_times(visited, times, -1, -1)
#print (max_time)
#for i in range(len(times)):
#        visited = [False for time in times]
#        total_times.append(times[i]['end'] - times[i]['start'] + get_times(visited[i+1:], times[i+1:], i, -1))
#total_times.sort()

#print (total_times)


#def get_times(v_1, v_2, times_1, times_2, visited_1, visited_2):
#    time_1 = times_1[v_1]
#    time_2 = times_2[v_2]
#
#    for adj_1 in adj_lists[v_1]:
#        if not visited_1[adj_1] or not visited_2[adj_1]:
#            for adj_2 in adj_lists[v_2]:
#                if not visited_1[adj_2] or not visited_2[adj_2]:
#
#            sm =  dfs_util(adj, visited)
#            sums.append(sm)



def get_times(v_1, v_2, times_1, times_2, visited, time_prev_1 = 0, time_prev_2 = 0):
    sums = []
    max_sum = 0
    visited[v_1] = True
    visited[v_2] = True

    
    for i in range(len(times_1)):
        time_1 = time_prev_1 + times_1[i]['end'] - times_1[i]['start']
        print ("time_1: ", time_1)
        for j in range(len(times_2)):
            time_2 = time_prev_2 + times_2[j]['end'] - times_2[j]['start']
            print ("time_2: ", time_2)
            for adj_1 in adj_lists[i]:
                if not visited[adj_1]:
                    for adj_2 in adj_lists[j]:
                        if not visited[adj_2]:
                            sm =  get_times(adj_1, adj_2, times_1, times_2, visited, time_1, time_2)
                            #print(sm)
                            sums.append(sm)

    if len(sums) > 0:
        max_sum = max(sums)
    
    return max_sum

def chechAdj(i_cur, i_prev):
    if i_prev == -1 or times[i_cur]['start'] >= times[i_prev]['end']:
        return True
    return False

def max_time(times, prev_a=-1, prev_b=-1, cur_index=0, a=0, b=0, c=0):
    #print (cur_index)
    if cur_index == len(times):
        #all_times.append(a+b+c)
        #all_times.append(b)
        #all_times.append(c)
        return a+b+c
    
    cur_time = times[cur_index]
    time_length = cur_time['end'] - cur_time['start']
    #print ("a: ", a)
    #print ("b: ", b)
    #print ("c: ", c)
    #print ("prev_b: ", prev_b )
    #print (cur_index)
    #print (cur_time)
    #print (time_length)
    max_time_1 = 0
    max_time_2 = 0
    max_time_3 = 0
    if chechAdj(cur_index, prev_a):
        max_time_1 = max_time(times, cur_index, prev_b, cur_index+1, a+time_length, b, c)
        
    if chechAdj(cur_index, prev_b):
        max_time_2 = max_time(times, prev_a, cur_index, cur_index+1, a, b+time_length, c)
    
    max_time_3 = max_time(times, prev_a, prev_b, cur_index+1, a, b, c)

    max_time_0 = max(max_time_1, max_time_2, max_time_3)
               
        
    return max_time_0



all_times = []
print (max_time(times))

#for i in range(len(times)):
#    for j in range(i+1, len(times)):
#        visited = [False for time in times]        
#        total_times.append(get_times(i, j, times, times[j:], visited, 0, 0))

#print(max(all_times))

