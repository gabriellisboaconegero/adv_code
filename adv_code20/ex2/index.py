#%%
import os 
dir_path = os.path.dirname(os.path.realpath(__file__))

first = None
second = None

def main():
  with open(f'{dir_path}/input.txt', 'r') as data:
    data = [line.strip() for line in data.readlines()]
    valid_passports_1 = valid_passports_2 = 0
    for line in data:
      policy, password = [_str.strip() for _str in line.split(':')]
      policy_numbers, policy_letter = policy.split()
      num1, num2 = [int(num) for num in policy_numbers.split('-')]

      #first
      if num1 <= password.count(policy_letter) <= num2:
        valid_passports_1 += 1
      
      #second
      if (password[num1 - 1] == policy_letter) ^ (password[num2 - 1] == policy_letter):
        valid_passports_2 += 1


    first = valid_passports_1
    second = valid_passports_2
  print(first)
  print(second)

if __name__ == '__main__':
    main()
# %%
