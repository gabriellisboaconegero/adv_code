#! /usr/bin/nodejs

var fs = require('fs');

var input;
if (0){
    input = 'teste.txt';
}else{
    input = 'input.txt';
}

function part1(){
    fs.readFile(input, 'utf8', function(err, data){
        if (err){
            return console.log(err);
        }

        let elf_pairs = data.split('\n');
        elf_pairs = elf_pairs.slice(0, elf_pairs.length - 1);
        elf_pairs = elf_pairs.map(x => 
            x.split(',').map(a => a.split('-').map(b => parseInt(b)))
        );

        elf_pairs = elf_pairs.filter(ranges => {
            let elf1 = ranges[0];
            let elf2 = ranges[1];
            return ((elf1[0] >= elf2[0]) && (elf1[1] <= elf2[1])) || ((elf2[0] >= elf1[0]) && (elf2[1] <= elf1[1]))
        });

        console.log(elf_pairs.length);
    });
}

function part2(){
    fs.readFile(input, 'utf8', function(err, data){
        if (err){
            return console.log(err);
        }

        let elf_pairs = data.split('\n');
        elf_pairs = elf_pairs.slice(0, elf_pairs.length - 1);

        let total_pairs = elf_pairs.length;
        elf_pairs = elf_pairs.map(x => 
            x.split(',').map(a => a.split('-').map(b => parseInt(b)))
        );

        elf_pairs = elf_pairs.filter(ranges => {
            let elf1 = ranges[0];
            let elf2 = ranges[1];
            return (elf1[1] < elf2[0]) || (elf2[1] < elf1[0]);
        });

        console.log(total_pairs - elf_pairs.length);
    });
    
}

part2();
