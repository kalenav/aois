function intToBinaryArr(num, places)
{
  var binaryArr = [];
  while(binaryArr.length < places)
  {
    binaryArr.push(num % 2);
    num = Math.floor(num / 2);
  }
  return binaryArr.reverse();
}

function createTruthTable(additiveType, states)
{
  if(!(additiveType instanceof Boolean) || !(states instanceof Number) || (states % 1 != 0))
  {
    console.log("Incorre")
  }
  var argumentQuantity = 1;
  while(Math.pow(2, argumentQuantity) < states) argumentQuantity++;
  var truthTable = new Array(3 * argumentQuantity + 1);
  var rows = [];
  for(let i = 0; i < truthTable.length; i++) 
  {
    truthTable[i] = new Array(states * 2);
    if(i >= 0 && i < argumentQuantity) rows.push('q*' + String(argumentQuantity - i));
    if(i >= argumentQuantity && i < argumentQuantity * 2) rows.push('q' + String(argumentQuantity * 2 - i));
    if(i == argumentQuantity * 2) rows.push('V');
    if(i > argumentQuantity * 2 && i < truthTable.length) rows.push('h' + String(truthTable.length - i));
  }
  var currTMinusOneState = additiveType ? 0 : states - 1;
  for(let j = 0; j < states * 2; j++)
  {
    var currStateInBinary = intToBinaryArr(currTMinusOneState, argumentQuantity);
    for(let i = 0; i < argumentQuantity; i++)
    {
      truthTable[i][j] = currStateInBinary[i];
    }
    j++;
    for(let i = 0; i < argumentQuantity; i++)
    {
      truthTable[i][j] = currStateInBinary[i];
    }
    additiveType ? currTMinusOneState++ : currTMinusOneState--;
  }
  for(let j = 0; j < states * 2; j++)
  {
    for(let i = argumentQuantity; i < argumentQuantity * 2; i++)
    {
      truthTable[i][j] = truthTable[i - argumentQuantity][(j + 1) % (states * 2)];
    }
  }
  for(let j = 0; j < states * 2; j++)
  {
    for(let i = argumentQuantity * 2; i < argumentQuantity * 3; i++)
    {
      if(truthTable[i - argumentQuantity * 2][j] != truthTable[i - argumentQuantity][j]) truthTable[i][j] = 1;
      else truthTable[i][j] = 0;
    }
  }
  for(let j = 0; j < states * 2; j++) truthTable[truthTable.length - 1][j] = j % 2;
  return [truthTable, rows];
}

function get_hi_function(rows, i)
{
  var result = "V";
  var currTrigger = 1;
  while(i > currTrigger) result += " * q*" + String(currTrigger++);
  return result; 
}