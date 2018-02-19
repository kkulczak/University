const zad2 = Array.from({length: 100000}, (v, k) => k + 1).filter(
    (elem) => {
        const digits = Array.from(elem.toString()).map((elem1) => Number(elem1));
        digits.push(digits.reduce((acc,value) => acc + value, 0));
        return digits.reduce((acc,value) => {
            return acc && (elem % value === 0);
        },true);
    }
);
console.log(zad2.slice(9,20))

let zad3 = Array.from({length: 100000 - 1}, (v, k) => k + 2)
for (var i = 0; i < zad3.length; i++) {
    const value = zad3[i];
    zad3 = zad3.filter( (item => {
        return item <= value ||  item % value !== 0;
    }))
}
console.log(zad3);
