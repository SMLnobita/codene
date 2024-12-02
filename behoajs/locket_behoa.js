//Scipt Locket_GOLD by Nguyen Hoa
const mapping = {
  '%E8%BD%A6%E7%A5%A8%E7%A5%A8': ['vip+watch_vip'],
  'Locket': ['Gold']
};

var ua = $request.headers["User-Agent"] || $request.headers["user-agent"];
var obj = JSON.parse($response.body);

obj.Attention = "Script by Nguyen Hoa";

var subscriptionTemplate = {
  is_sandbox: false,
  ownership_type: "PURCHASED",
  billing_issues_detected_at: null,
  period_type: "normal",
  expires_date: "2099-12-18T01:04:17Z",
  grace_period_expires_date: null,
  unsubscribe_detected_at: null,
  original_purchase_date: "2024-07-28T01:04:18Z",
  purchase_date: "2024-07-28T01:04:17Z",
  store: "app_store"
};

var entitlementTemplate = {
  grace_period_expires_date: null,
  purchase_date: "2024-07-28T01:04:17Z",
  product_identifier: "com.nguyenhoa.premium.yearly",
  expires_date: "2099-12-18T01:04:17Z"
};

const match = Object.keys(mapping).find(e => ua.includes(e));
if (match) {
  let [entitlementKey, subscriptionKey] = mapping[match];
  if (subscriptionKey) {
    entitlementTemplate.product_identifier = subscriptionKey;
    obj.subscriber.subscriptions[subscriptionKey] = { ...subscriptionTemplate };
  } else {
    obj.subscriber.subscriptions["com.nguyenhoa.premium.yearly"] = { ...subscriptionTemplate };
  }
  obj.subscriber.entitlements[entitlementKey] = { ...entitlementTemplate };
} else {
  obj.subscriber.subscriptions["com.nguyenhoa.premium.yearly"] = { ...subscriptionTemplate };
  obj.subscriber.entitlements["pro"] = { ...entitlementTemplate };
}

$done({ body: JSON.stringify(obj) });
