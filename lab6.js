var hashTable;
var hashTableSize;

function HashTableElement(key, val)
{
  this.key = key;
  this.value = val;
  this.next = null;
}

function allocHashTable(size)
{
  hashTable = new Array(size).fill(null);
  hashTableSize = size;
}

function getHashValue(input)
{
  return input.split('').reduce(((r, v, i) => r + input.charCodeAt(i) * Math.pow(27, input.length - 1 - i)), 0) % hashTableSize;
}

function addElementByKey(key, value)
{
  if(searchForElementByKey(key))
  {
    console.log("Such a key already exists in the hash table");
    return;
  }
  var keyValue = getHashValue(key);
  var newElement = new HashTableElement(key, value);
  if(hashTable[keyValue] != undefined)
  {
    for(let i = 0; i < hashTableSize; i++)
    {
      if(hashTable[i] == undefined)
      {
        hashTable[i] = newElement;
        return;
      }
    }
    newElement.next = hashTable[keyValue];
    hashTable[keyValue] = newElement;
  }
  else hashTable[keyValue] = newElement;
}

function searchForElementByKey(key)
{
  for(let i = 0; i < hashTable.length; i++)
  {
    var currElement = hashTable[i];
    if(currElement == undefined) continue;
    while(currElement != null)
    {
      if(currElement.key == key) return currElement.value;
      currElement = currElement.next;
    }
  }
  return undefined;
}

function deleteElementByKey(key)
{
  if(!searchForElementByKey(key))
  {
    console.log("There is no such key in the hash table");
    return;
  }
  var hashValue = getHashValue(key);
  var currElement = hasTable[hashValue];
  if(currElement != undefined)
  {
    if(currElement.key == key)
    {
      hashTable[i] = currElement.next;
      delete currElement;
      return;
    }
    while(currElement.next != null && currElement.next.key != key) currElement = currElement.next;
    if(currElement.key == key)
    {
    hashTable[i] = currElement.next;
      delete currElement;
      return;
    }
  }
  for(let i = 0; i < hashTable.length; i++)
  {
    if(i == hashValue) continue;
    currElement = hashTable[i];
    if(currElement == undefined) continue;
    if(currElement.key == key)
    {
      hashTable[i] = currElement.next;
      if(hashTable[i] != null) hashTable[i].first = true;
      delete currElement;
      return;
    }
    while(currElement.next != null && currElement.next.key != key) currElement = currElement.next;
    if(currElement.key == key)
    {
      hashTable[i] = currElement.next;
      if(hashTable[i] != null) hashTable[i].first = true;
      delete currElement;
      return;
    }
  }
}