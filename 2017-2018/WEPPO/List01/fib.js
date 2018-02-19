function fibIt(n) {
    if ([1, 2].includes(n))
        return 1;
    let data = [1, 1];
    for (var i = 2; i < n; i++) {
        const temp = data[0]
        data[0] = data[1];
        data[1] = temp + data[0];
    }
    return data[1];
}

function fibRec(n) {
    if ([1, 2].includes(n))
        return 1;
    return fibRec(n - 1) + fibRec(n - 2)
}

function countTime(f) {
    const start = new Date()
    f();
    const end = new Date()
    return end.getTime() - start.getTime()
}

list = [1, 10, 20, 30, 32, 35]
odp1 = list.slice().map(i => countTime(() =>fibIt(i)))
odp2 = list.slice().map(i => countTime(() =>fibRec(i)))
console.log(odp1, odp2)
