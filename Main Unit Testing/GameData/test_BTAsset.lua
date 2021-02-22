test_BTAsset = {}

function test_BTAsset.OnStart(me, them)

end

function test_BTAsset.OnDestory(me, them)

end

function test_BTAsset.Update(me, delta)
	DebugLog("BTAsset Update", delta);
end

function test_BTAsset.PrintTask(me, data)
	number = GetValueAsInt(me, "testKey");
	DebugLog("BTAsset Task print", number);
end