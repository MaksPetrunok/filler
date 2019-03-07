#!/usr/bin/php
<?php

    function parse_player($str, &$players) {
        $matches = array();
        $name = preg_match("/[a-z]*\.filler/", $str, $matches);
        if ($str[10] == '1')
            $players['O'] = $matches[0];
        else
            $players['X'] = $matches[0];
    }

    function get_map($str, &$score, $players) {
        global $delay;
        $map = array();
        $tmp = explode(' ', $str);
        $n = intval($tmp[1]);
        $w = intval($tmp[2]);
        fgets(STDIN);
        $score['O'] = 0;
        $score['X'] = 0;
        for ($i = 0; $i < $n; $i++) {
            $line = trim(explode(' ', fgets(STDIN))[1]);
            for ($j = 0; $j < strlen($line) - 1; $j++) {
                if ($line[$j] == '.')
                    continue;
                if ($line[$j] == 'O' || $line[$j] == 'o')
                    $score['O']++;
                else
                    $score['X']++;
            }
            $s = str_replace('.', ' ', "| " . $line . " |\n");
            $s = str_replace('O', '•', $s);
            $s = str_replace('X', '█', $s);
            $s = str_replace('o', '•', $s);
            $s = str_replace('x', '█', $s);
            $map[] = $s;
        }
        $sum = $score['O'] + $score['X'];
        $name_len = max(strlen($players['O']), strlen($players['X']));
        system('clear');
        echo str_repeat(" ", $w / 2 - 8) . ">>> MAP " . $tmp[1] . "x" . $w . " <<<\n";
        echo "/" . str_repeat( '-', $w + 2) . "\\\n";
        for ($i = 0; $i < $n; $i++) {
            echo $map[$i];
        }
        echo "\\" . str_repeat( '-', $w + 2) . "/\n\n";
        printf("%s:\n%s\n",
            $players['O'],
            str_repeat('•', intval($score['O'] * $w / $sum )));
        printf("%s:\n%s\n\n",
            $players['X'],
            str_repeat('█', intval($score['X'] * $w / $sum )));
        usleep($delay * 1000);
    }

    function skip_piece($str) {
        $tmp = explode(' ', $str);
        $n = intval($tmp[1]);
        for ($i = 0; $i <= $n; $i++) {
            fgets(STDIN);
        }
    }

    $players = array('X' => "", 'O' => "");
    $score = array('X' => 0, 'O' => 0);
    if ($argv[1] == '-d' && !empty($argv[2]))
        $delay = intval($argv[2]);
    else
        $delay = 0;

    while($str = trim(fgets(STDIN))) {
        if ($str[0] == '$') {
            parse_player($str, $players);
            continue;
        }
        if (preg_match("#Plateau*#", $str)) {
            get_map($str, $score, $players);
            continue;
        }
        if (preg_match("#Piece*#", $str)) {
            skip_piece($str);
            continue;
        }
        if ($str[0] == '=') {
            printf(">>> %s wins! <<<\n", $score['O'] > $score['X'] ? $players['O'] : $players['X']);
            die(0);
        }
    }