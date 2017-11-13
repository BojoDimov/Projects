// Using DFS to search for accepting solution
let solution = [];

function main() {
  let n = parseInt(process.argv[2]);
  if (isNaN(n)) {
    throw "Usage `node task1.js N`";
  }
  let len = n * 2 + 1;
  let frogs = Array(len);
  frogs[n] = 0;
  for (let i = 0; i < n; i++) {
    frogs[i] = -1;
    frogs[len - 1 - i] = 1;
  }

  let result = step(frogs);

  for (let i = solution.length - 1; i >= 0; i--) {
    console.log(solution[i]);
  }
}

function step(immutable) {
  if (check(immutable, (immutable.length - 1) / 2)) {
    registerStep(immutable);
    return true;
  }
  let frogs = immutable.slice(0);
  let free = frogs.indexOf(0);
  if (free > 0 && frogs[free - 1] == -1) {
    // >_ ~~~> _>
    frogs[free] = -1;
    frogs[free - 1] = 0;

    if (step(frogs)) {
      registerStep(immutable);
      return true;
    }
  }

  frogs = immutable.slice(0);

  if (free > 1 && frogs[free - 2] == -1 && frogs[free - 1] == 1) {
    // ><_ ~~~> _<>
    frogs[free - 2] = 0;
    frogs[free] = -1;

    if (step(frogs)) {
      registerStep(immutable);
      return true;
    }
    // else {
    //   frogs[free - 2] = -1;
    //   frogs[free] = 0;
    // }
  }

  frogs = immutable.slice(0);

  if (free < frogs.length - 1 && frogs[free + 1] == 1) {
    // _< ~~~> <_
    frogs[free] = 1;
    frogs[free + 1] = 0;

    if (step(frogs)) {
      registerStep(immutable);
      return true;
    }
  }

  frogs = immutable.slice(0);

  if (free < frogs.length - 2 && frogs[free + 2] == 1 && frogs[free + 1] == -1) {
    // _>< ~~~> <>_
    frogs[free + 2] = 0;
    frogs[free] = 1;

    if (step(frogs)) {
      registerStep(immutable);
      return true;
    }
  }

  return false;
}

function registerStep(step) {
  solution.push(step.join('').replace(/-1/g, ">").replace(/1/g, "<").replace(/0/g, "_"));
}

function check(frogs, n) {
  if (frogs[n] != 0) return false;
  for (let i = 0; i < n; i++) {
    if (frogs[i] == -1 || frogs[n * 2 - i] == 1) {
      return false;
    }
  }
  return true;
}

main();