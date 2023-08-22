#%%
import os 
dir_path = os.path.dirname(os.path.realpath(__file__))

def main():
  first = 0
  second = 0
  with open(f'{dir_path}/input.txt', 'r') as data:
    data = [x.replace("\n", " ") for x in data.read().split("\n\n")]
    questionsAnsweredYes = [set(x.replace(" ", '')) for x in data]
    for question in questionsAnsweredYes:
      first += len(question)
    
    for allAnswers in data:
      allAnswers = [set(x) for x in allAnswers.split()]
      tempSet = allAnswers[0]      
      for answer in allAnswers[1:]:
        tempSet = tempSet.intersection(answer)
      second += len(tempSet)
  print(first)
  print(second)

if __name__ == '__main__':
    main()
# %%
