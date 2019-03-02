Tree.prototype.say = function() {console.log('saying')};
Tree.prototype = {[Symbol.iterator]:GenIterator};

function * GenIterator (){
    const stack = [this];
    while (stack.length) {
        const item = stack.pop();
        if (typeof item !== 'object') {
            yield item;
        } else {
            if (item.right !== undefined) {
                stack.push(item.right);
            }
            stack.push(item.value);
            if (item.left !== undefined) {
                stack.push(item.left);
            }
        }
    }
}




var root = new Tree('root',new Tree(1), new Tree('son',new Tree('gradson')));

console.log(Symbol.iterator)
for ( var e of root ){
    console.log( e );
}