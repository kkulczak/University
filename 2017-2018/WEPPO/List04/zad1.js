var Tree = function(value, left, right) {
    this.value = value;
    this.left = left;
    this.right = right;
}

var root = new Tree('root',new Tree(1), new Tree('son',new Tree('gradson')));

console.log(root)
