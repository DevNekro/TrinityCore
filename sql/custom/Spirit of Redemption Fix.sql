--Fix Spirit of Redemption
SET @ENTRY := 27827;
DELETE FROM spell_script_names WHERE spell_id = @ENTRY;
INSERT INTO spell_script_names (spell_id, ScriptName) VALUES
(@ENTRY, 'spell_pri_spirit_of_redemption');