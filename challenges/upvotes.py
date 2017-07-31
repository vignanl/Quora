def max_count(ranges):
    count = 0
    for i in range(len(ranges)):
        index = ranges[i]
        val = index[1]-index[0] + 2
        val = (val*(val-1))/2
        count = count + val

    return count

def calculate(array,pat,win_size):
    k = win_size
    ranges = []
    patterns_length = []
    ans = []
    for i in range(k):
        if array[i] == pat or array[i] == 0:
            if not ranges:
                ans = [i,i]
                ranges.append(ans)
            else:
                ans = ranges[-1]
                if ans[-1] == i-1:
                    ans[-1] = i
                    ranges[-1] = ans
                else:
                    ans = [i,i]
                    ranges.append(ans)
    count = max_count(ranges)
    patterns_length.append(count)

    for i in range(k,len(array)):
        if not ranges:
            if array[i] == pat or arrray[i] == 0:
                ans = [i,i]
                ranges.append(ans)
        else:
            ans = ranges[0]
            if ans[0] == i-k:
                ans[0] = i-k+1
                if ans[0] > ans[1]:
                    del ranges[0]
                else:
                    ranges[0] = ans
            if array[i] == pat or array[i] == 0:
                if not ranges:
                    ans = [i,i]
                    ranges.append(ans)
                else:
                    ans = ranges[-1]
                    if ans[-1] == i-1:
                        ans[-1] = i
                        ranges[-1] = ans
                    else:
                        ans = [i,i]
                        ranges.append(ans)
        count = max_count(ranges)
        patterns_length.append(count)

    return patterns_length

def main():
    n,k = map(int,raw_input().split())
    upvotes = map(int,raw_input().split())

#   transform into sequence array of 1 and -1
    sequence = [0  for i in range(n-1)]
    for i in range(n-1):
        if upvotes[i] < upvotes[i+1]:
            sequence[i] = 1
        elif upvotes[i] > upvotes[i+1]:
            sequence[i] = -1
        else :
            sequence[i] = 0

#   calculate the count of non incresing sequences
    count_non_increasing = calculate(sequence,1,k-1)

#   calculate the count of non decreasing sequences
    count_non_decreasing = calculate(sequence,-1,k-1)

    n = len(count_non_increasing)
    for i in range(n):
        print count_non_increasing[i] - count_non_decreasing[i]

if __name__ == '__main__':
    main()
