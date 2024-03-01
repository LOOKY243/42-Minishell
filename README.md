# ***MINISHELL***

---

> ### ***ALL THE THING TO DO***
>
>> - `echo "|" cat` **->** 
>>   - `| cat`
>> - `export qq== && export ee$qq=hi` **->**
>>   - `qq==`
>>   - `ee==hi`
>> - `cat <<eof` **->**
>>   - `$PATH` is replaced by env var
>>   - `$PATHP` is replaced by env var
>>   - `$PATH^` is replaced by env var
>> - `cat <<'eof'` **->**
>>   - `$PATH` isn't replaced
>> - `cat <<"eof"` **->**
>>  - `$PATH` isn't replaced