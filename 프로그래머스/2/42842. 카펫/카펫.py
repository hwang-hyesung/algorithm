def solution(brown, yellow):
    answer = []
    
    for i in range(1, yellow + 1):
        if yellow % i == 0:
            w = max(i + 2, yellow // i + 2)
            h = min(i + 2, yellow // i + 2)
            if 2 * (w + h) - 4 == brown:
                answer = [w, h]
                break
    return answer
